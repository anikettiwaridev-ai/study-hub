<script setup>
// One question, laid out like a row of the exam paper: number and marks in the
// margin, the question in the body. Repeat badges are looked up automatically.
import { computed, onMounted, ref, watch } from 'vue'
import { withBase } from 'vitepress'
import { useSubject } from '../lib/subject.js'
import { parseRef, marksOf, relationsFor, refLabel, refTitle, refHref } from '../lib/refs.js'
import { isDone, setDone, doneVersion } from '../lib/progress.js'

const props = defineProps({
  id: { type: String, required: true },  // e.g. "S24.Q2"
  marks: { type: [Number, String], default: null },
  title: { type: String, default: '' },   // optional short topic line
  subject: { type: String, default: '' }, // only needed outside a subject's folder
})

const { id: subject, data } = useSubject(() => props.subject)
const parsed = computed(() => parseRef(props.id))
const marks = computed(() => props.marks ?? marksOf(props.id, data.value.sources))
const relations = computed(() => relationsFor(props.id, data.value.clusters))

const done = ref(false)
onMounted(() => (done.value = isDone(subject.value, props.id)))
watch(doneVersion, () => (done.value = isDone(subject.value, props.id)))
function toggleDone() {
  setDone(subject.value, props.id, !done.value)
}

const MAX_VARIANTS = 4
const chip = (r) => ({
  ref: r,
  label: refLabel(r, data.value.sources),
  title: refTitle(r, data.value.sources),
  href: refHref(r, data.value.sources),
})
</script>

<template>
  <section class="q-row" :id="parsed.anchor" :class="{ 'is-done': done }">
    <div class="q-margin">
      <span class="q-no">{{ parsed.partLabel }}</span>
      <span v-if="marks != null" class="q-marks">{{ marks }} {{ marks == 1 ? 'mark' : 'marks' }}</span>
      <button type="button" class="q-tick" :aria-pressed="done" @click="toggleDone"
              :aria-label="done ? `Mark ${parsed.partLabel} as not done` : `Mark ${parsed.partLabel} as done`">
        <span class="q-tick-box" aria-hidden="true"></span>
        <span class="q-tick-text">{{ done ? 'Done' : 'Mark done' }}</span>
      </button>
    </div>

    <div class="q-body">
      <p v-if="title" class="q-title">{{ title }}</p>

      <div v-for="rel in relations" :key="rel.cluster.id" class="q-repeat">
        <a class="q-repeat-count" :href="withBase(`/${subject}/repeats#${rel.cluster.id}`)"
           :title="`Open “${rel.cluster.title}” in the repeat map`">
          Asked {{ rel.count }} times
        </a>
        <span class="q-repeat-topic">{{ rel.cluster.title }}</span>
        <span v-if="rel.exact.length" class="q-rel exact">
          <span class="q-rel-kind" title="Word for word">⟳ Exact</span>
          <template v-for="c in rel.exact.map(chip)" :key="c.ref">
            <a v-if="c.href" class="chip" :href="withBase(c.href)" :title="c.title">{{ c.label }}</a>
            <span v-else class="chip" :title="c.title">{{ c.label }}</span>
          </template>
        </span>
        <span v-if="rel.reworded.length" class="q-rel reworded">
          <span class="q-rel-kind" title="Same question, different wording">≈ Reworded</span>
          <template v-for="c in rel.reworded.map(chip)" :key="c.ref">
            <a v-if="c.href" class="chip" :href="withBase(c.href)" :title="c.title">{{ c.label }}</a>
            <span v-else class="chip" :title="c.title">{{ c.label }}</span>
          </template>
        </span>
        <span v-if="rel.variant.length" class="q-rel variant">
          <span class="q-rel-kind" title="Same structure, different data or names">Δ Variant</span>
          <template v-for="c in rel.variant.slice(0, MAX_VARIANTS).map(chip)" :key="c.ref">
            <a v-if="c.href" class="chip" :href="withBase(c.href)" :title="c.title">{{ c.label }}</a>
            <span v-else class="chip" :title="c.title">{{ c.label }}</span>
          </template>
          <a v-if="rel.variant.length > MAX_VARIANTS" class="chip more"
             :href="withBase(`/${subject}/repeats#${rel.cluster.id}`)">
            {{ rel.variant.length - MAX_VARIANTS }} more
          </a>
        </span>
      </div>

      <slot />
    </div>
  </section>
</template>
