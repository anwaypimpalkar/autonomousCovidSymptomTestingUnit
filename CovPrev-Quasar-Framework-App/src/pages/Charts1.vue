<template>
  <q-page padding>
    <div>
      <apexchart width="500" type="bar" :options="options" :series="series"></apexchart>
    </div>
  </q-page>
</template>

<script>
  import Vue from 'vue'
  import {VueApexCharts} from 'vue-apexcharts'
  Vue.use(VueApexCharts)
  Vue.component('apexchart', VueApexCharts)
  
  export default {

  }
</script>
