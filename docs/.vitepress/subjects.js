// Every subject in the hub. Add a new one here and create docs/<id>/index.md.
// `sidebar` is what shows on the left inside that subject.

export const subjects = [
  {
    id: 'oop',
    code: 'AIN3002',
    name: 'Object Oriented Programming',
    faculty: 'Dr. Satnam Kaur',
    status: 'Quiz and mid-semester',
    sidebar: [
      {
        text: 'Start here',
        items: [
          { text: 'What to study, in order', link: '/oop/' },
          { text: 'How to answer', link: '/oop/how-to-answer' },
          { text: 'Most-trapped questions', link: '/oop/traps' },
          { text: 'How often questions repeat', link: '/oop/repeats' },
        ],
      },
      {
        text: 'Past papers',
        collapsed: false,
        items: [
          { text: 'All papers', link: '/oop/papers/' },
          { text: 'Sep 2024 mid-semester', link: '/oop/papers/mst-2024-sep' },
          { text: 'Oct 2024 remedial', link: '/oop/papers/mst-2024-remedial' },
          { text: 'Oct 2025 mid-semester', link: '/oop/papers/mst-2025-oct' },
          { text: 'Nov 2025 remedial', link: '/oop/papers/mst-2025-nov' },
          { text: 'Nov 2024 end-semester (part)', link: '/oop/papers/endsem-2024' },
          { text: 'Quiz 1', link: '/oop/papers/quiz-1' },
        ],
      },
      {
        text: 'Practice',
        items: [
          { text: 'Mock mid-semester paper', link: '/oop/mock-mst' },
          { text: 'Quiz practice', link: '/oop/quiz-practice' },
        ],
      },
      {
        text: 'Notes',
        collapsed: false,
        items: [
          { text: 'Overview', link: '/oop/notes/' },
          { text: 'Unit 1 · OOP concepts', link: '/oop/notes/unit-1' },
          { text: 'Unit 2 · Programming basics', link: '/oop/notes/unit-2' },
          { text: 'Unit 3 · Classes and objects', link: '/oop/notes/unit-3' },
          { text: 'Unit 4 · Operators and conversions', link: '/oop/notes/unit-4' },
        ],
      },
      {
        text: 'Assignments',
        collapsed: true,
        items: [
          { text: 'Overview', link: '/oop/assignments/' },
          { text: 'Assignment 5 (start here)', link: '/oop/assignments/a5' },
          { text: 'Assignment 1', link: '/oop/assignments/a1' },
          { text: 'Assignment 2', link: '/oop/assignments/a2' },
          { text: 'Assignment 3', link: '/oop/assignments/a3' },
          { text: 'Assignment 4', link: '/oop/assignments/a4' },
        ],
      },
    ],
  },
  { id: 'ds', code: 'AIN3001', name: 'Data Structures', faculty: 'Sudesh Rani' },
  { id: 'dsml', code: 'AIN3003', name: 'Data Science and Machine Learning', faculty: 'Shailendra Singh' },
  { id: 'mfai', code: 'AIN3004', name: 'Mathematical Foundations of AI', faculty: 'Nitin Kumar' },
]

// A subject is live once it has a sidebar.
export const liveSubjects = subjects.filter((s) => s.sidebar)
