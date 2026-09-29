// "Done" marks, stored per device. Keys look like hub:done:oop:S24.Q2
import { ref } from 'vue'

export const doneVersion = ref(0) // bumps on every change so counters re-read

const key = (subject, id) => `hub:done:${subject}:${id}`

export function isDone(subject, id) {
  try { return localStorage.getItem(key(subject, id)) === '1' } catch { return false }
}

export function setDone(subject, id, value) {
  try {
    if (value) localStorage.setItem(key(subject, id), '1')
    else localStorage.removeItem(key(subject, id))
  } catch {}
  doneVersion.value++
}

export function countDone(subject) {
  let n = 0
  try {
    const prefix = `hub:done:${subject}:`
    for (let i = 0; i < localStorage.length; i++) {
      if (localStorage.key(i)?.startsWith(prefix)) n++
    }
  } catch {}
  return n
}
