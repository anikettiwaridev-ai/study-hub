<script setup>
// Fill in the blank, for quiz practice.
//   <FillIn q="Static variables live in the ____." answer="data segment|data" />
// `answer` lists every accepted answer, separated by |. The first one is shown
// as "the answer". Matching ignores case, extra spaces and a trailing full stop.
// Anything in the slot is shown as the explanation after checking.
import { computed, ref } from 'vue'
import { inline } from '../lib/refs.js'

const props = defineProps({
  q: { type: String, required: true },
  answer: { type: String, required: true },
})

const norm = (s) => String(s).toLowerCase().replace(/\s+/g, ' ').replace(/[.;]+$/, '').trim()
const accepted = computed(() => props.answer.split('|').map(norm))
const shown = computed(() => props.answer.split('|')[0])

const value = ref('')
const state = ref('') // '' | 'right' | 'wrong' | 'revealed'

function check() {
  if (!value.value.trim()) return
  state.value = accepted.value.includes(norm(value.value)) ? 'right' : 'wrong'
}
function reveal() { state.value = 'revealed' }
function reset() { value.value = ''; state.value = '' }
</script>

<template>
  <div class="fill" :class="state">
    <p class="fill-q" v-html="inline(q)"></p>
    <form class="fill-row" @submit.prevent="check">
      <input v-model="value" class="fill-input" type="text" autocomplete="off" autocapitalize="off"
             spellcheck="false" :disabled="state === 'right' || state === 'revealed'"
             aria-label="Your answer" placeholder="Your answer" />
      <button v-if="state !== 'right' && state !== 'revealed'" type="submit" class="mcq-check" :disabled="!value.trim()">Check</button>
      <button v-if="state === '' || state === 'wrong'" type="button" class="mcq-reset" @click="reveal">Show answer</button>
      <button v-if="state !== ''" type="button" class="mcq-reset" @click="reset">Try again</button>
    </form>
    <p v-if="state === 'right'" class="mcq-result is-right" role="status">Correct.</p>
    <p v-else-if="state === 'wrong'" class="mcq-result is-wrong" role="status">Not quite. Try again, or show the answer.</p>
    <p v-else-if="state === 'revealed'" class="mcq-result" role="status">Answer: <strong v-html="inline(shown)"></strong></p>
    <div v-if="state === 'right' || state === 'revealed'" class="mcq-explain"><slot /></div>
  </div>
</template>
