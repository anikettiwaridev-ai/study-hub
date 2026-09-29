<script setup>
// The home page: every subject in the semester, laid out like a paper's question table.
import { withBase } from 'vitepress'
import { subjects } from '../../subjects.js'
</script>

<template>
  <div class="hub">
    <header class="hub-head">
      <h1 class="hub-title">Semester 3</h1>
      <p class="hub-lede">
        Past papers, assignments and notes for B.Tech CSE (AI) at Punjab Engineering College.
        Every program is compiled and run before it appears here.
      </p>
    </header>

    <table class="hub-table">
      <thead>
        <tr>
          <th scope="col" class="hub-code">Code</th>
          <th scope="col">Subject</th>
          <th scope="col" class="hub-status">Ready for</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="s in subjects" :key="s.id" :class="{ live: s.sidebar }">
          <td class="hub-code">{{ s.code }}</td>
          <td>
            <a v-if="s.sidebar" :href="withBase(`/${s.id}/`)" class="hub-name">{{ s.name }}</a>
            <span v-else class="hub-name">{{ s.name }}</span>
            <span class="hub-faculty">{{ s.faculty }}</span>
            <span class="hub-status-inline">{{ s.sidebar ? s.status : 'Not added yet' }}</span>
          </td>
          <td class="hub-status">{{ s.sidebar ? s.status : 'Not added yet' }}</td>
        </tr>
      </tbody>
    </table>

    <p class="hub-install">
      On your phone, open this site in Chrome and choose <strong>Install app</strong>.
      After the first visit it works offline.
      <a :href="withBase('/guide')">How to use it</a>
    </p>
  </div>
</template>
