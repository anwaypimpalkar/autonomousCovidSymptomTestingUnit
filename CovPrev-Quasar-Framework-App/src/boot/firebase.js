
import Vue from 'vue'
import * as  VueApexCharts from 'vue-apexcharts'
import firebase from "firebase/app";

import "firebase/auth";
import "firebase/database";

var firebaseConfig = {
  apiKey: "AIzaSyCGCuDMfFdYlKMS4V3U_SS8DwNnurn_syM",
  authDomain: "covprev-2021.firebaseapp.com",
  databaseURL: "https://covprev-2021-default-rtdb.firebaseio.com",
  projectId: "covprev-2021",
  storageBucket: "covprev-2021.appspot.com",
  messagingSenderId: "946198658981",
  appId: "1:946198658981:web:4f72d0548329fce1ff324c",
  measurementId: "G-8JK8PLJNJW"
};

let firebaseApp = firebase.initializeApp(firebaseConfig);
let firebaseAuth = firebaseApp.auth();
let firebaseDb = firebase.database();

Vue.use(VueApexCharts)
Vue.component('apexchart', VueApexCharts)


export default async ({ store }) => {
  store.dispatch("sensor/fbReadData", firebaseDb);
  store.dispatch("deviceStatus/fbReadData", firebaseDb);
  store.dispatch("deviceStatus/updateTime")
};
