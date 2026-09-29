// Works out which subject a page belongs to from its path, unless told explicitly.
import { computed, toValue } from 'vue'
import { useData } from 'vitepress'
import { subjectData } from '../data/index.js'

const EMPTY = { sources: {}, clusters: [], singles: [] }

export function useSubject(explicit) {
  const { page } = useData()
  const id = computed(() => toValue(explicit) || page.value.relativePath.split('/')[0])
  const data = computed(() => subjectData[id.value] ?? EMPTY)
  return { id, data }
}
