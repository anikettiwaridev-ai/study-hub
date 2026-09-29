#!/usr/bin/env node
// Checks every subject's repeat data before a deploy:
//   every ref points at a real paper and question,
//   every mid-semester question is filed exactly once (so mark totals add up),
//   cluster ids are unique.
import { subjectData } from '../docs/.vitepress/theme/data/index.js'
import { parseRef } from '../docs/.vitepress/theme/lib/refs.js'

const problems = []

for (const [subject, { sources, clusters, singles }] of Object.entries(subjectData)) {
  const seen = new Map() // ref -> where it was filed
  const ids = new Set()

  const file = (ref, where) => {
    const { src, main } = parseRef(ref)
    if (!sources[src]) problems.push(`${subject}: ${where} uses unknown source "${src}" in ${ref}`)
    else if (!(main in sources[src].parts)) problems.push(`${subject}: ${where} uses ${ref}, but ${src} has no ${main}`)
    if (sources[src]?.kind === 'mst') {
      if (seen.has(ref)) problems.push(`${subject}: ${ref} is filed twice (${seen.get(ref)} and ${where}); mark totals would double-count`)
      seen.set(ref, where)
    }
  }

  for (const c of clusters) {
    if (ids.has(c.id)) problems.push(`${subject}: duplicate cluster id ${c.id}`)
    ids.add(c.id)
    const refs = c.groups.flatMap((g) => g.refs)
    if (new Set(refs).size !== refs.length) problems.push(`${subject}: ${c.id} lists a ref twice`)
    refs.forEach((r) => file(r, c.id))
    for (const n of Object.keys(c.notes ?? {})) {
      if (!refs.includes(n)) problems.push(`${subject}: ${c.id} has a note for ${n}, which is not in the cluster`)
    }
  }
  singles.forEach((s) => file(s.ref, 'singles'))

  for (const [src, s] of Object.entries(sources)) {
    if (s.kind !== 'mst') continue
    for (const part of Object.keys(s.parts)) {
      if (!seen.has(`${src}.${part}`)) problems.push(`${subject}: ${src}.${part} is not filed in any cluster or in singles`)
    }
  }
}

if (problems.length) {
  console.error(`Repeat data has ${problems.length} problem(s):\n  ${problems.join('\n  ')}`)
  process.exit(1)
}
console.log(`Repeat data OK for: ${Object.keys(subjectData).join(', ')}.`)
