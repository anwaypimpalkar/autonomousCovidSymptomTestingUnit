<template>
  <q-layout view="lHh Lpr lFf">
    <q-header>
      <q-toolbar>
        <q-btn
          flat
          dense
          round
          icon="menu"
          aria-label="Menu"
          @click="leftDrawerOpen = !leftDrawerOpen"
        />

        
      </q-toolbar>
      <div class = "q-px-lg q-pt-xl q-mb-md">
        <div class = "text-h3">CovPrev</div>
        <div class ="text-subtitle1">Autonomous Covid Symptom Testing Unit</div>
        <div class ="text-subtitle1">{{todaysDate}}</div>

      </div>
      <q-img
        src = "~assets/drawer-header.jpg"
        class="header-image absolute-top"
      />  
    </q-header>

    <q-drawer
      v-model="leftDrawerOpen"
      show-if-above
      :breakpoint="900"
      bordered
      content-class="bg-grey-1"
    >
    <q-scroll-area class="fit"><!--style="height: calc(100% - 220px); margin-top: 220px;"-->
      <q-list>
        <q-item-label header class="text-grey-8">
          Navigation
        </q-item-label>
        <q-item to="/" exact clickable>
          <q-item-section avatar>
            <q-icon name="multiline_chart" />
          </q-item-section>

          <q-item-section>
            <q-item-label>Data Analytics</q-item-label>
            <q-item-label caption>
              Check Data Overview and Patterns
            </q-item-label>
          </q-item-section>
        </q-item>
        <q-item to="/device" exact clickable>
          <q-item-section avatar>
            <q-icon name="clean_hands" />
          </q-item-section>

          <q-item-section>
            <q-item-label>Device</q-item-label>
            <q-item-label caption>
              Monitor Device Status
            </q-item-label>
          </q-item-section>
        </q-item>
        <q-item to="/settings" exact clickable>
          <q-item-section avatar>
            <q-icon name="rule" />
          </q-item-section>

          <q-item-section>
            <q-item-label>Settings</q-item-label>
            <q-item-label caption>
              Callibrate Sensors and App
            </q-item-label>
          </q-item-section>
        </q-item>
        <!-- <q-item-label header class="text-grey-8">
          More
        </q-item-label> -->
        <q-item to="/project" exact clickable>
          <q-item-section avatar>
            <q-icon name="auto_stories" />
          </q-item-section>

          <q-item-section>
            <q-item-label>The Project</q-item-label>
            <q-item-label caption>
              Project and Group Details
            </q-item-label>
          </q-item-section>
        </q-item>
        <!-- <q-item to="/safety" exact clickable>
          <q-item-section avatar>
            <q-icon name="social_distance" />
          </q-item-section>
          <q-item-section>
            <q-item-label>Safety Guidelines</q-item-label>
            <q-item-label caption>
              Safeguard Yourself From COVID-19
            </q-item-label>
          </q-item-section>
        </q-item> -->
      </q-list>
      </q-scroll-area>
      <!-- <q-img class="menu-image absolute-top" src="~assets/drawer-header.jpg" style="height: 220px">
          <div class="absolute-bottom bg-transparent">
            <div class="text-weight-bold" color="black">CovPrev</div>
            <div>@rstoenescu</div>
          </div>
        </q-img> -->
    </q-drawer>

    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>
</template>

<script>

import { date } from 'quasar'

export default {
  name: "MainLayout",
  data() {
    return {
      leftDrawerOpen: false
    };
  },
  computed: {
    todaysDate(){
      let timeStamp = Date.now()
      return date.formatDate(timeStamp, 'dddd, Do MMMM YYYY')
    }
  }
};
</script>

<style lang = "scss">
  .header-image {
    height: 100%;
    z-index: -1;
    opacity: 0.7;
    filter: grayscale(50%)
  }
  .menu-image {
    height: 100%;
    filter: grayscale(80%)
  }
</style>