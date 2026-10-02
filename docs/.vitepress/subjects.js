// Every subject in the hub. Add a new one here and create docs/<id>/index.md.
// `sidebar` is that subject's part of the ONE sidebar shown on every page: it becomes a
// collapsible group named after the subject. Leave it out until the subject has pages.

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
  {
    id: 'ds',
    code: 'AIN3001',
    name: 'Data Structures',
    faculty: 'Sudesh Rani',
    status: 'Mid-semester and quizzes',
    sidebar: [
      {
        text: 'Start here',
        items: [
          { text: 'What to study, in order', link: '/ds/' },
          { text: 'How to answer the mid-sem', link: '/ds/how-to-answer' },
          { text: 'Beat the 10-minute quiz clock', link: '/ds/quiz-clock' },
          { text: 'Most-trapped questions', link: '/ds/traps' },
          { text: 'How often questions repeat', link: '/ds/repeats' },
        ],
      },
      {
        text: 'Notes',
        collapsed: false,
        items: [
          { text: 'Overview', link: '/ds/notes/' },
          { text: 'Unit 1 · Complexity, recursion, pointers', link: '/ds/notes/unit-1' },
          { text: 'Unit 2 · Linked lists', link: '/ds/notes/unit-2' },
          { text: 'Unit 3 · Stacks and expressions', link: '/ds/notes/unit-3' },
          { text: 'Unit 4 · Queues', link: '/ds/notes/unit-4' },
          { text: 'Unit 5 · Trees', link: '/ds/notes/unit-5' },
        ],
      },
      {
        text: 'Past papers',
        collapsed: false,
        items: [
          { text: 'All papers', link: '/ds/papers/' },
          { text: 'Oct 2025 mid-semester', link: '/ds/papers/mst-2025-oct' },
          { text: '2024 mid-semester (Paper B)', link: '/ds/papers/mst-2024-b' },
          { text: 'Mar 2024 mid-semester (Paper A)', link: '/ds/papers/mst-2024-mar' },
          { text: 'Sep 2023 mid-semester', link: '/ds/papers/mst-2023-sep' },
          { text: 'Oct 2022 mid-semester (Paper A)', link: '/ds/papers/mst-2022-a' },
          { text: '2022 mid-semester (Paper B)', link: '/ds/papers/mst-2022-b' },
          { text: 'Dec 2024 end-semester', link: '/ds/papers/endsem-2024' },
          { text: 'Dec 2023 end-semester', link: '/ds/papers/endsem-2023' },
        ],
      },
      {
        text: 'Quizzes',
        collapsed: true,
        items: [
          { text: 'All quizzes', link: '/ds/quizzes/' },
          { text: '2026 Theory Quiz 1', link: '/ds/quizzes/2026-theory-1' },
          { text: '2026 Theory Quiz 2', link: '/ds/quizzes/2026-theory-2' },
          { text: '2026 Lab Quiz 1', link: '/ds/quizzes/2026-lab-1' },
          { text: '2026 Lab Quiz 2', link: '/ds/quizzes/2026-lab-2' },
          { text: '2025 Theory Quiz I', link: '/ds/quizzes/2025-theory-1' },
          { text: '2025 Theory Quiz II', link: '/ds/quizzes/2025-theory-2' },
          { text: '2025 Theory Quiz III', link: '/ds/quizzes/2025-theory-3' },
          { text: '2025 Theory Quiz IV', link: '/ds/quizzes/2025-theory-4' },
          { text: '2025 Lab Quiz I', link: '/ds/quizzes/2025-lab-1' },
          { text: '2025 Lab Quiz II', link: '/ds/quizzes/2025-lab-2' },
          { text: '2025 Lab Quiz III', link: '/ds/quizzes/2025-lab-3' },
        ],
      },
      {
        text: 'Practice',
        items: [
          { text: 'Mock mid-semester paper', link: '/ds/mock-mst' },
          { text: 'Practice sheets', link: '/ds/practice/' },
          { text: 'Sheet 1 · Classes and pointers', link: '/ds/practice/sheet-1' },
          { text: 'Sheet 2 · Linked lists', link: '/ds/practice/sheet-2' },
          { text: 'Sheet 3 · Stacks and queues', link: '/ds/practice/sheet-3' },
        ],
      },
    ],
  },
  { id: 'dsml', code: 'AIN3003', name: 'Data Science and Machine Learning', faculty: 'Shailendra Singh' },
  { id: 'mfai', code: 'AIN3004', name: 'Mathematical Foundations of AI', faculty: 'Nitin Kumar' },
]

// A subject is live once it has a sidebar.
export const liveSubjects = subjects.filter((s) => s.sidebar)
