// Helpers for refs like "S24.Q2" or "A2.Q3-i".

export function parseRef(ref) {
  const dot = ref.indexOf('.')
  const src = ref.slice(0, dot)
  const part = ref.slice(dot + 1)
  const [main, sub] = part.split('-')
  return {
    src,
    part,
    main,
    partLabel: sub ? `${main} (${sub})` : main,
    anchor: main.toLowerCase(),
  }
}

export function refLabel(ref, sources) {
  const { src, partLabel } = parseRef(ref)
  const s = sources[src]
  return s ? `${s.short} ${partLabel}` : ref
}

export function refTitle(ref, sources) {
  const { src, partLabel } = parseRef(ref)
  const s = sources[src]
  return s ? `${s.title}, ${partLabel}` : ref
}

// Site-relative path, or null while the source page doesn't exist yet.
export function refHref(ref, sources) {
  const { src, anchor } = parseRef(ref)
  const s = sources[src]
  return s && s.href ? `${s.href}#${anchor}` : null
}

export function marksOf(ref, sources) {
  const { src, main } = parseRef(ref)
  const s = sources[src]
  return s ? (s.parts[main] ?? null) : null
}

// Every cluster containing `ref`, with the other appearances split by label.
export function relationsFor(ref, clusters) {
  const out = []
  for (const c of clusters) {
    const all = c.groups.flatMap((g) => g.refs)
    if (!all.includes(ref)) continue
    const mine = c.groups.find((g) => g.refs.includes(ref))
    const same = mine.refs.filter((r) => r !== ref)
    out.push({
      cluster: c,
      count: all.length,
      exact: mine.kind === 'exact' ? same : [],
      reworded: mine.kind === 'reworded' ? same : [],
      variant: c.groups.filter((g) => g !== mine).flatMap((g) => g.refs),
    })
  }
  return out
}

// Escapes HTML, then turns `code` spans into <code>.
export function inline(text = '') {
  return text
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/`([^`]+)`/g, '<code>$1</code>')
}
