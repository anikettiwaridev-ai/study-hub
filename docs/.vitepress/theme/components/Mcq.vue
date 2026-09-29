<script setup>
// Multiple choice. `answer` is a letter ("d") or several ("c,d").
import { computed, ref } from 'vue'
import { inline } from '../lib/refs.js'

const props = defineProps({
  options: { type: Array, required: true },
  answer: { type: String, required: true },
})

const letters = 'abcdefghijklmnopqrstuvwxyz'
const correct = computed(() => props.answer.split(',').map((s) => s.trim().toLowerCase()))
const multi = computed(() => correct.value.length > 1)

const picked = ref([])
const checked = ref(false)

function pick(letter) {
  if (checked.value) return
  if (!multi.value) {
    picked.value = [letter]
    checked.value = true
    return
  }
  picked.value = picked.value.includes(letter)
    ? picked.value.filter((l) => l !== letter)
    : [...picked.value, letter]
}

const right = computed(
  () => checked.value
    && picked.value.length === correct.value.length
    && picked.value.every((l) => correct.value.includes(l)),
)

function state(letter) {
  if (!checked.value) return picked.value.includes(letter) ? 'picked' : ''
  if (correct.value.includes(letter)) return 'correct'
  if (picked.value.includes(letter)) return 'wrong'
  return 'dim'
}

function reset() {
  picked.value = []
  checked.value = false
}
</script>

<template>
  <div class="mcq">
    <p v-if="multi" class="mcq-hint">More than one option is correct. Pick all of them, then check.</p>
    <ol class="mcq-options" type="a">
      <li v-for="(opt, i) in options" :key="i">
        <button type="button" class="mcq-opt" :class="state(letters[i])"
                :aria-pressed="picked.includes(letters[i])" :disabled="checked" @click="pick(letters[i])">
          <span class="mcq-letter">{{ letters[i] }})</span>
          <span v-html="inline(String(opt))"></span>
        </button>
      </li>
    </ol>
    <div class="mcq-actions">
      <button v-if="multi && !checked" type="button" class="mcq-check" :disabled="!picked.length" @click="checked = true">
        Check answer
      </button>
      <template v-if="checked">
        <p class="mcq-result" :class="right ? 'is-right' : 'is-wrong'" role="status">
          {{ right ? 'Correct.' : `Not quite. The answer is ${correct.join(' and ')}.` }}
        </p>
        <button type="button" class="mcq-reset" @click="reset">Try again</button>
      </template>
    </div>
    <div v-if="checked" class="mcq-explain"><slot /></div>
  </div>
</template>
