<script setup>
// Inline reference to another question, e.g. <Src r="A5.Q3" />
import { computed } from 'vue'
import { withBase } from 'vitepress'
import { useSubject } from '../lib/subject.js'
import { refLabel, refTitle, refHref } from '../lib/refs.js'

const props = defineProps({ r: { type: String, required: true }, subject: { type: String, default: '' } })
const { data } = useSubject(() => props.subject)
const label = computed(() => refLabel(props.r, data.value.sources))
const title = computed(() => refTitle(props.r, data.value.sources))
const href = computed(() => refHref(props.r, data.value.sources))
</script>

<template>
  <a v-if="href" class="chip" :href="withBase(href)" :title="title">{{ label }}</a>
  <span v-else class="chip" :title="title">{{ label }}</span>
</template>
