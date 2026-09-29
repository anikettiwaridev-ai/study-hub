<script setup>
// "N of M questions marked done on this device."
import { computed, onMounted, ref, watch } from 'vue'
import { useSubject } from '../lib/subject.js'
import { countDone, doneVersion } from '../lib/progress.js'

const { id, data } = useSubject()
const total = computed(() =>
  Object.values(data.value.sources).reduce((n, s) => n + Object.keys(s.parts).length, 0),
)
const done = ref(0)
const refresh = () => (done.value = countDone(id.value))
onMounted(refresh)
watch(doneVersion, refresh)
</script>

<template>
  <div class="progress" role="status">
    <div class="progress-track" aria-hidden="true">
      <span class="progress-fill" :style="{ '--p': total ? done / total : 0 }"></span>
    </div>
    <p>
      <strong>{{ done }} of {{ total }}</strong> questions marked done on this device.
      <span v-if="done === 0">Tick “Mark done” beside a question once you can answer it without looking.</span>
    </p>
  </div>
</template>
