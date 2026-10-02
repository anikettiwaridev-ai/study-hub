<script setup>
// A countdown that stays in view while you scroll, for practising under quiz time.
//   <QuizTimer :minutes="10" label="Theory quiz" />
import { computed, onBeforeUnmount, ref } from 'vue'

const props = defineProps({
  minutes: { type: Number, default: 10 },
  label: { type: String, default: 'Quiz time' },
})

const total = computed(() => props.minutes * 60)
const left = ref(props.minutes * 60)
const running = ref(false)
let tick = null

const mmss = computed(() => {
  const s = Math.max(0, left.value)
  return `${Math.floor(s / 60)}:${String(s % 60).padStart(2, '0')}`
})
const state = computed(() => (left.value <= 0 ? 'out' : left.value <= 120 ? 'low' : ''))

function stop() { clearInterval(tick); tick = null; running.value = false }
function toggle() {
  if (running.value) return stop()
  if (left.value <= 0) left.value = total.value
  running.value = true
  tick = setInterval(() => {
    left.value--
    if (left.value <= 0) stop()
  }, 1000)
}
function reset() { stop(); left.value = total.value }
onBeforeUnmount(stop)
</script>

<template>
  <div class="quiz-timer" :class="state" role="timer" :aria-label="`${label}: ${mmss} left`">
    <span class="qt-label">{{ label }}</span>
    <span class="qt-clock">{{ left <= 0 ? 'Time' : mmss }}</span>
    <button type="button" class="qt-btn" @click="toggle">{{ running ? 'Pause' : left === total ? 'Start' : left <= 0 ? 'Again' : 'Resume' }}</button>
    <button type="button" class="qt-btn ghost" @click="reset" :disabled="left === total && !running">Reset</button>
  </div>
</template>
