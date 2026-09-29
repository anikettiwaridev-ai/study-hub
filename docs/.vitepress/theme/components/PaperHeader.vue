<script setup>
// The key/value block at the top of an exam paper.
defineProps({ rows: { type: Array, required: true } }) // [[label, value], ...]
</script>

<template>
  <dl class="paper-header">
    <div v-for="[k, v] in rows" :key="k" class="ph-row">
      <dt>{{ k }}</dt>
      <dd>{{ v }}</dd>
    </div>
  </dl>
</template>
