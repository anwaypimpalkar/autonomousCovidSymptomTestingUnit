<template>
  <q-page padding>
    <q-card flat bordered class="my-card">
      <q-card-section>
        <div class = "row">
        <div class="text-h6 q-mt-xs col-6">
          Recent Data
        </div>
        <div class = "col-6">
        <!-- <q-btn
          outline
          v-if = "!loading"
          class = "float-right"
          color="primary"
          icon-right="download"
          label="Export to CSV"
          no-caps
          @click="exportTable"
        /> -->
        </div>
        </div>
      </q-card-section>
      <q-separator />
      <div v-if = "loading" align = "center">
        <q-markup-table flat>
        <thead>
          <tr>
            <th class="text-center">
              <q-skeleton animation="wave" type="text" />
            </th>
            <th class="text-center">
              <q-skeleton animation="wave" type="text" />
            </th>
            <th class="text-center">
              <q-skeleton animation="wave" type="text" />
            </th>
            <th class="text-center">
              <q-skeleton animation="wave" type="text" />
            </th>
          </tr>
        </thead>

        <tbody>
          <tr v-for="n in 6" :key="n">
            <td class="text-center">
              <q-skeleton animation="wave" type="text" width="45px" />
            </td>
            <td class="text-center">
              <q-skeleton animation="wave" type="text" width="45px" />
            </td>
            <td class="text-center">
              <q-skeleton animation="wave" type="text" width="45px" />
            </td>
            <td class="text-center">
              <q-skeleton animation="wave" type="text" width="45px" />
            </td>
          </tr>
        </tbody>
      </q-markup-table>
      </div>
      <div v-else>
        <q-table
        flat 
          :data="data"
          :columns="columns"
          row-key="name"
          :rows-per-page-options="[5]"
          :pagination="initialPagination"
        >
        </q-table>
      </div>
    </q-card>
    <div class = "q-mt-sm"></div>
    <q-card flat bordered class="my-card">
      <q-card-section>
        <div class="text-h6 q-mt-xs">
          Temperature Variation Visualization
        </div>
        <q-separator class="q-mt-xs"/>
      <div id="chart" class="q-mt-xs">
        <apexchart type="line" height="350" :options="tempChartOptions" :series="series" ref="tempChart"></apexchart>
      </div>
      <div class="text-h6 q-mt-xs">
          Pulse Variation Visualization
        </div>
        <q-separator class="q-mt-xs"/>
        <div id="chart" class="q-mt-xs">
        <apexchart type="line" height="350" :options="pulseChartOptions" :series="series" ref="pulseChart"></apexchart>
      </div><div class="text-h6 q-mt-xs">
          SpO₂% Variation Visualization
        </div>
        <q-separator class="q-mt-xs"/>
        <div id="chart" class="q-mt-xs">
        <apexchart type="line" height="350" :options="spo2ChartOptions" :series="series" ref="spo2Chart"></apexchart>
      </div>
      </q-card-section>
    </q-card>
  </q-page>
</template>

<script>
import { exportFile } from 'quasar'
import {mapGetters } from "vuex"

function wrapCsvValue (val, formatFn) {
  let formatted = formatFn !== void 0
    ? formatFn(val)
    : val

  formatted = formatted === void 0 || formatted === null
    ? ''
    : String(formatted)

  formatted = formatted.split('"').join('""')
  return `"${formatted}"`
}
export default {
  watch: {
      getDataCount(newCount, oldCount) {

        this.$refs.tempChart.updateSeries([ {name:"Temperature", data: this.tempData} ])
        this.$refs.tempChart.updateOptions({xaxis: { categories: this.idData }})

        this.$refs.pulseChart.updateSeries([ {name:"Pulse", data: this.pulseData} ])
        this.$refs.pulseChart.updateOptions({xaxis: { categories: this.idData }})

        this.$refs.spo2Chart.updateSeries([ {name:"SpO2", data: this.spo2Data} ])
        this.$refs.spo2Chart.updateOptions({xaxis: { categories: this.idData }})
      }
  },
  mounted() {
    if (localStorage.getItem('reloaded')) {
        // The page was just reloaded. Clear the value from local storage
        // so that it will reload the next time this page is visited.
        localStorage.removeItem('reloaded');
    } else {
        // Set a flag so that we know not to reload the page twice.
        localStorage.setItem('reloaded', '1');
        location.reload();
    }
},
  data() {
    return {
      initialPagination: {
        sortBy: 'id', 
        descending: true,
      },
      columns: [
        {
          name: "timestamp",
          align: "center",
          label: "Timestamp",
          field: "timestamp"
        },
        {
          name: "temperature",
          align: "center",
          label: "Temperature",
          field: "temperature"
        },
        { name: "spo2", align: "center", label: "SpO₂", field: "spo2" },
        { name: "pulse", align: "center", label: "Pulse", field: "pulse" },
        {
          name: "id",
          label: "Data ID",
          align: "center",
          field: "id",
          sortable: true
        }
      ],
      data: this.$store.state.sensor.data,
      series: [{
          name: "",
          data: []
      }],
      tempChartOptions: {
        chart: {
          height: 350,
          type: 'line',
          zoom: {
            enabled: false
          },
        },
        dataLabels: {
          enabled: true
        },
        stroke: {
          width: 2,
          curve: 'straight',
        },
        legend: {
          tooltipHoverFormatter: function(val, opts) {
            return val + ' - ' + opts.w.globals.series[opts.seriesIndex][opts.dataPointIndex] + ''
          }
        },
        markers: {
          size: 0,
          hover: {
            sizeOffset: 6
          }
        },
        xaxis: {
          categories: []
        },
        tooltip: {
          y: [
            {
              title: {
                formatter: function (val) {
                  return val + " (°F)"
                }
              }
            }
          ]
        },
        grid: {
          borderColor: '#f1f1f1',
        },
        colors:['#496e92', '#496e92', '#496e92']
      },
      pulseChartOptions: {
        chart: {
          height: 350,
          type: 'line',
          zoom: {
            enabled: false
          },
        },
        dataLabels: {
          enabled: true
        },
        stroke: {
          width: 2,
          curve: 'straight',
        },
        legend: {
          tooltipHoverFormatter: function(val, opts) {
            return val + ' - ' + opts.w.globals.series[opts.seriesIndex][opts.dataPointIndex] + ''
          }
        },
        markers: {
          size: 0,
          hover: {
            sizeOffset: 6
          }
        },
        xaxis: {
          categories: []
        },
        tooltip: {
          y: [
            {
              title: {
                formatter: function (val) {
                  return val + " (BPM)"
                }
              }
            }
          ]
        },
        grid: {
          borderColor: '#f1f1f1',
        },
        colors:['#496e92', '#496e92', '#496e92']
      },
      spo2ChartOptions: {
        chart: {
          height: 350,
          type: 'line',
          zoom: {
            enabled: false
          },
        },
        dataLabels: {
          enabled: true
        },
        stroke: {
          width: 2,
          curve: 'straight',
        },
        legend: {
          tooltipHoverFormatter: function(val, opts) {
            return val + ' - ' + opts.w.globals.series[opts.seriesIndex][opts.dataPointIndex] + ''
          }
        },
        markers: {
          size: 0,
          hover: {
            sizeOffset: 6
          }
        },
        xaxis: {
          categories: []
        },
        tooltip: {
          y: [
            {
              title: {
                formatter: function (val) {
                  return val + " (%)"
                }
              }
            }
          ]
        },
        grid: {
          borderColor: '#f1f1f1',
        },
        colors:['#496e92', '#496e92', '#496e92']
      }
    };
  },
  computed: {
    loading() { 
      return this.$store.state.sensor.data.length > 0 ? false : true 
    },
    ...mapGetters({
      getDataCount: "sensor/getDataCount"
    }),
    tempData(){
      return  this.$store.getters['sensor/getTemp']
    },
    pulseData(){
      return  this.$store.getters['sensor/getPulse']
    },
    spo2Data(){
      return  this.$store.getters['sensor/getSpO2']
    },
    idData(){
      return  this.$store.getters['sensor/getID']
    },
    isTempDataAvail(){
      return this.tempData.length > 0 ? true : false
    }
  },
   methods: {
    exportTable () {
      const content = [ this.columns.map(col => wrapCsvValue(col.label)) ].concat(
        this.data.map(row => this.columns.map(col => wrapCsvValue(
          typeof col.field === 'function'
            ? col.field(row)
            : row[col.field === void 0 ? col.name : col.field],
          col.format
        )).join(','))
      ).join('\r\n')

      const status = exportFile(
        'covprevData.csv',
        content,
        'text/csv'
      )

      if (status !== true) {
        this.$q.notify({
          message: 'Browser denied file download...',
          color: 'negative',
          icon: 'warning'
        })
      }
    }
  },
};
</script>
