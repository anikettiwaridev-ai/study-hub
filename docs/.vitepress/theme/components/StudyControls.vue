<script setup>
import { onMounted } from 'vue'
import { solutionsHidden, trapsOnly, loadPrefs, savePrefs, applyToPage } from '../lib/study.js'

onMounted(loadPrefs)

function toggleSolutions() {
  solutionsHidden.value = !solutionsHidden.value
  savePrefs()
  applyToPage()
}
function toggleTraps() {
  trapsOnly.value = !trapsOnly.value
  savePrefs()
  applyToPage()
}
</script>

<template>
  <div class="study-controls" role="group" aria-label="Study controls">
    <button type="button" class="sc-btn" :aria-pressed="!solutionsHidden" @click="toggleSolutions"
            :title="solutionsHidden ? 'Open every solution on this page' : 'Close every solution on this page'">
      <span class="sc-long">{{ solutionsHidden ? 'Show solutions' : 'Hide solutions' }}</span>
      <span class="sc-short">Solutions</span>
    </button>
    <button type="button" class="sc-btn" :aria-pressed="trapsOnly" @click="toggleTraps"
            title="Show only traps and corrections">
      Traps only
    </button>
  </div>
</template>
