import { defineConfig } from 'vitepress'
import { withPwa } from '@vite-pwa/vitepress'
import { subjects, liveSubjects } from './subjects.js'

// GitHub Pages serves a project site from /<repo>/. The deploy workflow sets BASE.
const base = process.env.BASE || '/'
const repo = process.env.GITHUB_REPOSITORY // "user/repo" in CI, undefined locally

const PAPER = '#F2F5F8'

export default withPwa(
  defineConfig({
    base,
    lang: 'en-IN',
    title: 'Study hub',
    description: 'Past papers, assignments and notes for B.Tech CSE (AI), solved and checked.',
    lastUpdated: true,

    head: [
      ['link', { rel: 'icon', type: 'image/svg+xml', href: `${base}favicon.svg` }],
      ['link', { rel: 'apple-touch-icon', href: `${base}apple-touch-icon.png` }],
      ['meta', { name: 'theme-color', content: PAPER, media: '(prefers-color-scheme: light)' }],
      ['meta', { name: 'theme-color', content: '#111726', media: '(prefers-color-scheme: dark)' }],
    ],

    markdown: {
      container: {
        tipLabel: 'Rule',
        warningLabel: 'Correction',
        dangerLabel: 'Trap',
        infoLabel: 'Note',
        detailsLabel: 'Solution',
      },
      lineNumbers: false,
      // $…$ and $$…$$ are typeset at build time (MathJax to SVG), so formulas work offline.
      // fontCache 'local' shares glyph shapes within each formula, which cuts page size by about a quarter.
      math: { svg: { fontCache: 'local' } },
    },

    themeConfig: {
      logo: '/favicon.svg',
      siteTitle: 'Study hub',
      nav: [
        ...liveSubjects.map((s) => ({ text: s.id.toUpperCase(), link: `/${s.id}/` })),
        { text: 'Using this site', link: '/guide' },
      ],
      // One sidebar for the whole site. Every subject is a collapsible group; the group
      // holding the current page opens by itself. A subject without a sidebar yet still
      // gets a group, so the list of subjects is the same on every page.
      sidebar: [
        {
          text: 'Study hub',
          items: [
            { text: 'All subjects', link: '/' },
            { text: 'Using this site', link: '/guide' },
          ],
        },
        ...subjects.map((s) =>
          s.sidebar
            ? { text: s.name, collapsed: true, items: s.sidebar }
            : { text: s.name, collapsed: true, items: [{ text: 'Not added yet' }] },
        ),
      ],
      search: { provider: 'local' },
      outline: { level: [2, 3], label: 'On this page' },
      docFooter: { prev: 'Previous', next: 'Next' },
      lastUpdated: { text: 'Last updated' },
      darkModeSwitchLabel: 'Appearance',
      sidebarMenuLabel: 'Contents',
      returnToTopLabel: 'Back to top',
      notFound: {
        title: 'This page does not exist yet',
        quote: 'It may not have been added, or the link is out of date.',
        linkText: 'Go to the subject list',
      },
      ...(repo && {
        editLink: {
          pattern: `https://github.com/${repo}/edit/main/docs/:path`,
          text: 'Suggest a fix for this page',
        },
        socialLinks: [{ icon: 'github', link: `https://github.com/${repo}` }],
      }),
    },

    pwa: {
      registerType: 'autoUpdate',
      injectRegister: 'script-defer',
      includeAssets: ['favicon.svg', 'apple-touch-icon.png'],
      manifest: {
        name: 'Study hub',
        short_name: 'Study hub',
        description: 'Past papers, assignments and notes, solved and checked. Works offline.',
        start_url: base,
        scope: base,
        display: 'standalone',
        orientation: 'portrait',
        theme_color: PAPER,
        background_color: PAPER,
        icons: [
          { src: 'pwa-192.png', sizes: '192x192', type: 'image/png' },
          { src: 'pwa-512.png', sizes: '512x512', type: 'image/png' },
          { src: 'pwa-maskable-512.png', sizes: '512x512', type: 'image/png', purpose: 'maskable' },
        ],
      },
      workbox: {
        globPatterns: ['**/*.{css,js,html,svg,png,ico,txt,woff2,webmanifest}'],
        navigateFallback: null,
        cleanupOutdatedCaches: true,
      },
    },
  }),
)
