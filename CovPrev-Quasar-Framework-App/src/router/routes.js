
const routes = [
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    children: [
      { path: '', component: () => import('pages/Index.vue') },
      { path: '/device', component: () => import('pages/Device.vue') },
      { path: '/settings', component: () => import('pages/Settings.vue') },
      { path: '/project', component: () => import('pages/Project.vue') },
      { path: '/safety', component: () => import('pages/Safety.vue') },
      { path: '/charts', component: () => import('pages/Charts.vue') }

    ]
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: '*',
    component: () => import('pages/Error404.vue')
  }
]

export default routes
