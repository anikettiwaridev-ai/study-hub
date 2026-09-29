import DefaultTheme from 'vitepress/theme-without-fonts'
import { h, nextTick, onMounted, watch } from 'vue'
import { useRoute } from 'vitepress'

// Self-hosted fonts, Latin subset only, so they are cached for offline use.
import '@fontsource/ibm-plex-sans/latin-400.css'
import '@fontsource/ibm-plex-sans/latin-400-italic.css'
import '@fontsource/ibm-plex-sans/latin-600.css'
import '@fontsource/ibm-plex-serif/latin-600.css'
import '@fontsource/ibm-plex-mono/latin-400.css'
import './style.css'

import StudyControls from './components/StudyControls.vue'
import Q from './components/Q.vue'
import Mcq from './components/Mcq.vue'
import Src from './components/Src.vue'
import RepeatMap from './components/RepeatMap.vue'
import Progress from './components/Progress.vue'
import PaperHeader from './components/PaperHeader.vue'
import SourceTable from './components/SourceTable.vue'
import Hub from './components/Hub.vue'
import FillIn from './components/FillIn.vue'
import Drill from './components/Drill.vue'
import { loadPrefs, applyToPage, openActiveSidebarGroups, solutionsHidden, trapsOnly } from './lib/study.js'

export default {
  extends: DefaultTheme,

  Layout: () =>
    h(DefaultTheme.Layout, null, {
      'nav-bar-content-after': () => h(StudyControls),
    }),

  enhanceApp({ app }) {
    const components = { Q, Mcq, Src, RepeatMap, Progress, PaperHeader, SourceTable, Hub, FillIn, Drill }
    for (const [name, c] of Object.entries(components)) app.component(name, c)
  },

  // Re-apply "hide solutions" and "traps only" whenever the page changes.
  setup() {
    const route = useRoute()
    const settle = () => {
      applyToPage()
      setTimeout(openActiveSidebarGroups, 0)   // after the sidebar has rendered
    }
    onMounted(() => {
      loadPrefs()
      settle()
    })
    watch(() => route.path, () => nextTick(settle))
    watch([solutionsHidden, trapsOnly], () => nextTick(applyToPage))
  },
}
