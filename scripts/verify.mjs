#!/usr/bin/env node
// Compiles and runs every C++ program under code/, runs every Python script under
// code/, and writes each one's real output to <name>.out beside it. Pages import
// those .out files, so no output on the site is ever typed by hand.
//
//   npm run verify          regenerate every .out
//   npm run verify -- --check   fail if anything differs from what's committed (CI)
//
// Optional sidecar files next to <name>.cpp:
//   <name>.in       text fed to the program's standard input
//   <name>.expect   one word:
//                     compile-error     the program must NOT compile
//                     ub                undefined behaviour; output is not compared
//                     nondeterministic  e.g. garbage values; output is not compared
//                     platform          output depends on the machine (e.g. sizeof(long) is 4 on
//                                       Windows, 8 on Linux); compiled and run, not compared
//                     warning-ok        GCC warns "may be undefined" but the code is in fact
//                                       well defined (a false positive); output IS compared
//   <name>.with     extra source files (one per line, relative to this folder) that are
//                   compiled and linked together with <name>.cpp, e.g. a second module.
//                   Files whose name starts with "_" are never compiled on their own.
//
// Programs are compiled as standard C++17 with -pedantic-errors, so GCC extensions
// (things GCC accepts but the standard forbids) count as errors, the way an exam does.
//
// Python scripts (the DSML worked numericals) use the standard library only, so CI needs
// no packages. They run with code/<subject>/ on PYTHONPATH, so a shared helper such as
// code/dsml/_hub.py can be imported; files starting with "_" are never run on their own.
// A script's .out is usually a Markdown fragment that a page pulls in with
// <!--@include: @/../code/...out-->. The one Python .expect value:
//   recorded   the script needs packages CI does not have (the DSML lab assignments use
//              pandas and scikit-learn). Its .out files are a recorded run made by
//              scripts/record-labs.py; verify only checks that the main .out exists.

import { readdirSync, readFileSync, writeFileSync, existsSync, mkdtempSync, rmSync } from 'node:fs'
import { join, relative, basename, dirname } from 'node:path'
import { spawnSync } from 'node:child_process'
import { tmpdir } from 'node:os'
import { fileURLToPath } from 'node:url'

const ROOT = fileURLToPath(new URL('..', import.meta.url))
const CODE = join(ROOT, 'code')
const CHECK = process.argv.includes('--check')
const CXX = process.env.CXX || 'g++'
const FLAGS = ['-std=c++17', '-Wall', '-Wextra', '-pedantic-errors']
const EXE = process.platform === 'win32' ? '.exe' : ''

function walk(dir, ext) {
  if (!existsSync(dir)) return []
  return readdirSync(dir, { withFileTypes: true }).flatMap((e) =>
    e.isDirectory() ? walk(join(dir, e.name), ext) : e.name.endsWith(ext) && !e.name.startsWith('_') ? [join(dir, e.name)] : [],
  )
}

const tmp = mkdtempSync(join(tmpdir(), 'hub-verify-'))
const failures = []
let checked = 0

// Writes the .out, or in --check mode compares it with the committed one.
function record(rel, stem, output, expect) {
  const outFile = `${stem}.out`
  if (CHECK) {
    if (!existsSync(outFile)) { failures.push(`${rel}: no .out file committed. Run npm run verify.`); return }
    const compare = expect === 'ok' || expect === 'warning-ok'
    if (compare && readFileSync(outFile, 'utf8').replace(/\r\n/g, '\n').trimEnd() !== output.trimEnd()) {
      failures.push(`${rel}: output differs from ${basename(outFile)}. Run npm run verify and review the change.`)
      return
    }
  } else {
    writeFileSync(outFile, output)
  }
  checked++
}

// ---- C++ -------------------------------------------------------------------
let cppFiles = walk(CODE, '.cpp').sort()
const probe = spawnSync(CXX, ['--version'], { encoding: 'utf8' })
if (cppFiles.length && probe.status !== 0) {
  const msg = `Could not run ${CXX}. Install g++ (MinGW on Windows) or set CXX.`
  if (CHECK) { console.error(msg); process.exit(1) }
  console.warn(`${msg}\nSkipping C++: the committed .out files will be used as they are.`)
  cppFiles = []
}

for (const file of cppFiles) {
  const rel = relative(ROOT, file)
  const stem = file.slice(0, -4)
  const expect = existsSync(`${stem}.expect`) ? readFileSync(`${stem}.expect`, 'utf8').trim() : 'ok'
  const stdin = existsSync(`${stem}.in`) ? readFileSync(`${stem}.in`, 'utf8') : ''
  const exe = join(tmp, basename(stem) + EXE)
  const extra = existsSync(`${stem}.with`)
    ? readFileSync(`${stem}.with`, 'utf8').split(/\r?\n/).map((l) => l.trim()).filter(Boolean).map((f) => join(dirname(file), f))
    : []

  const cc = spawnSync(CXX, [...FLAGS, '-o', exe, file, ...extra], { encoding: 'utf8' })
  let output

  if (expect === 'compile-error') {
    if (cc.status === 0) { failures.push(`${rel}: expected a compile error, but it compiled`); continue }
    const lines = cc.stderr.split('\n')
    const line = lines.find((l) => /:\d+:\d+:\s*error:/.test(l)) ?? lines.find((l) => l.includes('error:')) ?? 'error'
    const m = line.match(/:(\d+):\d+:\s*error:\s*(.*)$/)
    const multi = lines.find((l) => l.includes('multiple definition of'))
    if (m) output = `Compile error on line ${m[1]}:\n${m[2]}\n`
    else if (multi) output = `Link error:\n${multi.slice(multi.indexOf('multiple definition of')).trim()}\n`
    else if (/ld returned/.test(line)) output = 'Link error:\nthe linker refused to build the program (see the explanation)\n'
    else output = `Compile error:\n${line.trim()}\n`
  } else {
    if (cc.status !== 0) { failures.push(`${rel}: does not compile\n${cc.stderr}`); continue }
    if (/-Wsequence-point|may be undefined/.test(cc.stderr) && expect !== 'ub' && expect !== 'warning-ok') {
      failures.push(`${rel}: the compiler warns of undefined behaviour. Add ${basename(stem)}.expect containing "ub" if that is intended.`)
      continue
    }
    const run = spawnSync(exe, [], { input: stdin, encoding: 'utf8', timeout: 5000 })
    if (run.error?.code === 'ETIMEDOUT') { failures.push(`${rel}: still running after 5 seconds`); continue }
    output = run.stdout.replace(/\r\n/g, '\n')
    if (!output.endsWith('\n')) output += '\n'
  }

  record(rel, stem, output, expect)
}

// ---- Python ----------------------------------------------------------------
const pyFiles = walk(CODE, '.py').sort()
const PY = [process.env.PYTHON, 'python3', 'python'].filter(Boolean).find((c) => {
  const r = spawnSync(c, ['--version'], { encoding: 'utf8' })
  return r.status === 0 && /Python 3/.test(`${r.stdout}${r.stderr}`)
})
if (pyFiles.length && !PY) {
  const msg = 'Could not run Python 3. Install it or set PYTHON.'
  if (CHECK) { console.error(msg); process.exit(1) }
  console.warn(`${msg}\nSkipping Python: the committed .out files will be used as they are.`)
}

for (const file of PY ? pyFiles : []) {
  const rel = relative(ROOT, file)
  const stem = file.slice(0, -3)
  const expect = existsSync(`${stem}.expect`) ? readFileSync(`${stem}.expect`, 'utf8').trim() : 'ok'
  if (expect === 'recorded') {
    if (!existsSync(`${stem}.out`)) failures.push(`${rel}: no recorded .out. Run scripts/record-labs.py with the lab's Python.`)
    else checked++
    continue
  }
  const subjectDir = join(CODE, relative(CODE, file).split(/[\\/]/)[0])
  const run = spawnSync(PY, ['-X', 'utf8', file], {
    encoding: 'utf8',
    timeout: 20000,
    cwd: dirname(file),
    env: { ...process.env, PYTHONPATH: subjectDir, PYTHONIOENCODING: 'utf-8', PYTHONDONTWRITEBYTECODE: '1' },
  })
  if (run.error?.code === 'ETIMEDOUT') { failures.push(`${rel}: still running after 20 seconds`); continue }
  if (run.status !== 0) { failures.push(`${rel}: exited with an error\n${run.stderr}`); continue }
  let output = run.stdout.replace(/\r\n/g, '\n')
  if (!output.endsWith('\n')) output += '\n'
  record(rel, stem, output, expect)
}

rmSync(tmp, { recursive: true, force: true })

if (failures.length) {
  console.error(`\n${failures.length} problem(s):\n\n${failures.join('\n\n')}\n`)
  process.exit(1)
}
console.log(`${checked} program(s) ${CHECK ? 'checked against committed output' : 'run and saved'}.`)
