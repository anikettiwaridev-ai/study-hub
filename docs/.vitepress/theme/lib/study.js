// Page-wide study controls, shared by every instance of StudyControls.
import { ref } from 'vue'

export const solutionsHidden = ref(true) // practice mode is the default
export const trapsOnly = ref(false)

const KEY_HIDDEN = 'hub:solutions-hidden'
const KEY_TRAPS = 'hub:traps-only'

let loaded = false
export function loadPrefs() {
  if (loaded || typeof window === 'undefined') return
  loaded = true
  try {
    solutionsHidden.value = localStorage.getItem(KEY_HIDDEN) !== '0'
    trapsOnly.value = localStorage.getItem(KEY_TRAPS) === '1'
  } catch {}
}

export function savePrefs() {
  try {
    localStorage.setItem(KEY_HIDDEN, solutionsHidden.value ? '1' : '0')
    localStorage.setItem(KEY_TRAPS, trapsOnly.value ? '1' : '0')
  } catch {}
}

// Opens or closes every solution on the page and sets the trap filter.
// Traps only opens solutions too, so traps written inside them can show.
export function applyToPage() {
  if (typeof document === 'undefined') return
  document.documentElement.classList.toggle('traps-only', trapsOnly.value)
  document
    .querySelectorAll('.vp-doc details.details')
    .forEach((d) => (d.open = trapsOnly.value || !solutionsHidden.value))
}

// The sidebar is one list for every subject, with each subject collapsed. Open the
// groups that contain the current page (VitePress does not do this for nested groups).
export function openActiveSidebarGroups() {
  if (typeof document === 'undefined') return
  for (let pass = 0; pass < 4; pass++) {
    const closed = document.querySelectorAll('.VPSidebar .VPSidebarItem.collapsed.has-active')
    if (!closed.length) break
    closed.forEach((g) => g.querySelector(':scope > .item')?.click())
  }
}
