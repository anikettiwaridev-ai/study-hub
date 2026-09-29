<script setup>
// One numbered practice item on a quiz page.
//   <Drill n="3" tag="Output">  ...question, then <Mcq> or <FillIn>...  </Drill>
defineProps({
  n: { type: [String, Number], required: true },
  tag: { type: String, default: '' },     // e.g. "Output", "Concept", "Fill in"
  from: { type: String, default: '' },    // optional source note, e.g. "v2 drill 6"
})
</script>

<template>
  <div class="drill">
    <div class="drill-head">
      <span class="drill-no">Q{{ n }}</span>
      <span v-if="tag" class="drill-tag">{{ tag }}</span>
      <span v-if="from">{{ from }}</span>
    </div>
    <slot />
  </div>
</template>
