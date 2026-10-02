<script setup>
// The ranked repeat map. Everything here is computed from the subject's data file.
import { computed } from 'vue'
import { withBase } from 'vitepress'
import { useSubject } from '../lib/subject.js'
import { parseRef, marksOf, refLabel, refTitle, refHref, inline } from '../lib/refs.js'

const props = defineProps({ part: { type: String, default: 'all' } }) // 'table' | 'clusters' | 'all'
const { data } = useSubject()
const sources = computed(() => data.value.sources)

const mstIds = computed(() =>
  Object.entries(sources.value).filter(([, s]) => s.kind === 'mst').map(([id]) => id),
)
const mstTotal = computed(() =>
  mstIds.value.reduce((n, id) => n + (sources.value[id].maxMarks ?? 0), 0),
)
const isPaper = (r) => ['mst', 'endsem', 'quiz'].includes(sources.value[parseRef(r).src]?.kind)
const isMst = (r) => sources.value[parseRef(r).src]?.kind === 'mst'
const mstMarks = (refs) => refs.filter(isMst).reduce((n, r) => n + (marksOf(r, sources.value) ?? 0), 0)

const rows = computed(() => {
  const list = data.value.clusters.map((c) => {
    const refs = c.groups.flatMap((g) => g.refs)
    return {
      c,
      refs,
      total: refs.length,
      papers: refs.filter(isPaper).length,
      marks: mstMarks(refs),
      assignments: refs.filter((r) => sources.value[parseRef(r).src]?.kind === 'assignment').length,
    }
  })
  return list.sort((a, b) => b.marks - a.marks || b.total - a.total)
})

const singlesMarks = computed(() => mstMarks(data.value.singles.map((s) => s.ref)))
const accounted = computed(() => rows.value.reduce((n, r) => n + r.marks, 0) + singlesMarks.value)
const maxMarks = computed(() => Math.max(1, ...rows.value.map((r) => r.marks)))

const kindLabel = { exact: '⟳ Exact', reworded: '≈ Reworded' }
// Subjects can rename the "assignments" column (DS has practice sheets instead).
const labels = computed(() => ({
  column: ['In assignments', 'In A1–A5'],
  word: 'assignments',
  uncovered: 'No assignment covers this. Study it from the notes.',
  ...(data.value.labels ?? {}),
}))
const chip = (r) => ({
  ref: r,
  label: refLabel(r, sources.value),
  title: refTitle(r, sources.value),
  href: refHref(r, sources.value),
  marks: isPaper(r) ? marksOf(r, sources.value) : null,
})
</script>

<template>
  <div class="repeat-map">
    <template v-if="part !== 'clusters'">
    <p class="rm-summary">
      The last {{ mstIds.length }} mid-semester papers carried {{ mstTotal }} marks.
      This table shows where they went, largest topic first.
      <template v-if="accounted !== mstTotal">
        <strong>Only {{ accounted }} are accounted for, so the data file is incomplete.</strong>
      </template>
    </p>

    <div class="rm-table-wrap">
      <table class="rm-table">
        <thead>
          <tr>
            <th scope="col">Topic</th>
            <th scope="col" class="num"><span class="rm-long">Mid-sem marks</span><span class="rm-short">Marks</span></th>
            <th scope="col" class="num"><span class="rm-long">Times asked</span><span class="rm-short">Asked</span></th>
            <th scope="col" class="num"><span class="rm-long">{{ labels.column[0] }}</span><span class="rm-short">{{ labels.column[1] }}</span></th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="row in rows" :key="row.c.id" :class="{ uncovered: row.c.uncovered }">
            <td><a :href="`#${row.c.id}`">{{ row.c.title }}</a></td>
            <td class="num">
              <span class="rm-bar" :style="{ '--w': row.marks / maxMarks }" aria-hidden="true"></span>
              {{ row.marks || '–' }}
            </td>
            <td class="num">{{ row.total }}</td>
            <td class="num">{{ row.assignments || 'none' }}</td>
          </tr>
          <tr class="rm-singles-row">
            <td><a href="#asked-once">Asked once</a></td>
            <td class="num">
              <span class="rm-bar" :style="{ '--w': singlesMarks / maxMarks }" aria-hidden="true"></span>
              {{ singlesMarks }}
            </td>
            <td class="num">{{ data.singles.length }}</td>
            <td class="num">–</td>
          </tr>
        </tbody>
      </table>
    </div>
    </template>

    <template v-if="part !== 'table'">
    <section v-for="row in rows" :key="row.c.id" :id="row.c.id" class="rm-cluster">
      <h3>
        {{ row.c.title }}
        <a class="header-anchor" :href="`#${row.c.id}`" :aria-label="`Link to ${row.c.title}`">&#8203;</a>
      </h3>
      <p class="rm-meta">
        Asked {{ row.total }} times: {{ row.papers }} in papers and quizzes, {{ row.assignments }} in {{ labels.word }}.
        <template v-if="row.marks">{{ row.marks }} mid-semester marks.</template>
      </p>
      <p v-if="row.c.uncovered" class="rm-uncovered">{{ labels.uncovered }}</p>
      <p v-if="row.c.trap" class="rm-trap" v-html="inline(row.c.trap)"></p>

      <ul class="rm-groups">
        <li v-for="(g, gi) in row.c.groups" :key="gi" :class="['rm-group', g.kind]">
          <span v-if="kindLabel[g.kind]" class="rm-kind">{{ kindLabel[g.kind] }}</span>
          <ul>
            <li v-for="c in g.refs.map(chip)" :key="c.ref">
              <a v-if="c.href" :href="withBase(c.href)" :title="c.title">{{ c.label }}</a>
              <span v-else :title="c.title">{{ c.label }}</span>
              <span v-if="c.marks" class="rm-marks">{{ c.marks }} marks</span>
              <span v-if="row.c.notes?.[c.ref]" class="rm-note" v-html="inline(row.c.notes[c.ref])"></span>
            </li>
          </ul>
        </li>
      </ul>
    </section>

    <section id="asked-once" class="rm-cluster">
      <h3>Asked once <a class="header-anchor" href="#asked-once" aria-label="Link to Asked once">&#8203;</a></h3>
      <p class="rm-meta">Appeared in a single paper. Still fair game.</p>
      <ul class="rm-singles">
        <li v-for="s in data.singles" :key="s.ref">
          <a v-if="refHref(s.ref, sources)" :href="withBase(refHref(s.ref, sources))">{{ refLabel(s.ref, sources) }}</a>
          <span v-else>{{ refLabel(s.ref, sources) }}</span>
          <span class="rm-note" v-html="inline(s.topic)"></span>
        </li>
      </ul>
    </section>
    </template>
  </div>
</template>
