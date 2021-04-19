<template>
  <q-page padding>  
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
import {mapGetters } from "vuex"

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
    computed: {
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
    data() {
      return {
      series: [{
          name: "",
          data: []
          }
        ],
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
      }
    }
  }
</script>
