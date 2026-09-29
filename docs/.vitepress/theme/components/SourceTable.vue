<script setup>
// Lists a subject's papers or assignments with how far each has got.
import { computed } from 'vue'
import { withBase } from 'vitepress'
import { useSubject } from '../lib/subject.js'

const props = defineProps({ kinds: { type: String, required: true } }) // "mst,endsem,quiz"
const { data } = useSubject()
const wanted = computed(() => props.kinds.split(','))
const rows = computed(() =>
  Object.entries(data.value.sources)
    .filter(([, s]) => wanted.value.includes(s.kind))
    .map(([id, s]) => ({ id, ...s, count: Object.keys(s.parts).length })),
)
const isAssignment = computed(() => wanted.value.includes('assignment'))
</script>

<template>
  <div class="st-wrap">
    <table class="st-table">
      <thead>
        <tr>
          <th scope="col">{{ isAssignment ? 'Assignment' : 'Paper' }}</th>
          <th v-if="!isAssignment" scope="col" class="num">Marks</th>
          <th scope="col" class="num">Questions</th>
          <th scope="col">Solutions</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="r in rows" :key="r.id">
          <td>
            <a v-if="r.href" :href="withBase(r.href)">{{ r.title }}</a>
            <span v-else>{{ r.title }}</span>
            <span v-if="r.topic || r.note" class="st-sub">{{ r.topic || r.note }}</span>
          </td>
          <td v-if="!isAssignment" class="num">{{ r.maxMarks ?? '–' }}</td>
          <td class="num">{{ r.count }}</td>
          <td>
            <span v-if="r.href" class="st-status ready">Solved and checked</span>
            <span v-else class="st-status">Not added yet</span>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>
