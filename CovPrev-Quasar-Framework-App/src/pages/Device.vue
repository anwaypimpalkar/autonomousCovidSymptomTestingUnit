<template>
  <div class="q-pa-md">
    <div class="row q-col-gutter-y-md">
      <div class="col-12">
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="row">
              <div class="col-8 text-h6">
                <div class="text-h6 q-mt-xs">
                  Device Status
                </div>
              </div>
              <div class="col-4">
                <q-chip v-if="isOnline" square class="col-4 float-right">
                  <q-avatar
                    icon="signal_wifi_4_bar"
                    color="green"
                    text-color="white"
                    class="on-right"
                  />
                  Online
                </q-chip>
                  <q-chip v-else square class="col-4 float-right">
                  <q-avatar
                    icon="signal_wifi_off"
                    color="red"
                    text-color="white"
                    class="on-right"
                  />
                  Offline
                </q-chip>
              </div>
            </div>
            
              <q-separator v-if="!isOnline"/>
          </q-card-section>
          <q-card-section class="q-pt-none" v-if="!isOnline">
            Last seen: {{ lastOnline }}
          </q-card-section>
        </q-card>
      </div>
      <div class="col-12">
        <q-card flat  bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Sensor Status</div>
            <q-separator />
          </q-card-section>

          <q-card-section class="q-pt-none">
            <q-card flat class="my-card">
              <q-card-section>
                <div class="row">
                  <div class="col-8">
                    <div class="q-mt-sm">
                      Temperature (MLX90614)
                    </div>
                  </div>
                  <div class="col-4">
                    <q-chip v-if="isOnline" square class="col-4 float-right">
                      <q-avatar
                        icon="check"
                        color="green"
                        text-color="white"
                        class="on-right"
                      />
                      Optimal
                    </q-chip>
                    <q-chip v-else square class="col-4 float-right">
                      <q-avatar
                        icon="block"
                        color="grey-8"
                        text-color="white"
                        class="on-right"
                      />
                      Offline
                    </q-chip>
                  </div>
                </div>
              </q-card-section>
            </q-card>
            <div class = "q-mt-xs"></div>
            <q-card flat class="my-card">
              <q-card-section>
                <div class="row">
                  <div class="col-8">
                    <div class="q-mt-sm">
                      Pulse Oximeter (MAX30100)
                    </div>
                  </div>
                  <div class="col-4">
                    <q-chip v-if="isOnline" square class="col-4 float-right">
                      <q-avatar
                        icon="check"
                        color="green"
                        text-color="white"
                        class="on-right"
                      />
                      Optimal
                    </q-chip>
                    <q-chip v-else square class="col-4 float-right">
                      <q-avatar
                        icon="block"
                        color="grey-8"
                        text-color="white"
                        class="on-right"
                      />
                      Offline
                    </q-chip>
                  </div>
                </div>
              </q-card-section>
            </q-card>
            <q-card flat class="my-card">
              <q-card-section>
                <div class="row">
                  <div class="col-8">
                    <div class="q-mt-sm">
                      Sanitizer Spray IR Trigger
                    </div>
                  </div>
                  <div class="col-4">
                    <q-chip v-if="isOnline" square class="col-4 float-right">
                      <q-avatar
                        icon="check"
                        color="green"
                        text-color="white"
                        class="on-right"
                      />
                      Optimal
                    </q-chip>
                    <q-chip v-else square class="col-4 float-right">
                      <q-avatar
                        icon="block"
                        color="grey-8"
                        text-color="white"
                        class="on-right"
                      />
                      Offline
                    </q-chip>
                  </div>
                </div>
              </q-card-section>
            </q-card>
          </q-card-section>
        </q-card>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      
    };
  },
  computed: {
    lastOnline(){
      const deviceTimestamp = this.$store.state.deviceStatus.status.timestamp
      const currentTimestamp = this.$store.state.deviceStatus.status.currentTime
      const secondsAgo = currentTimestamp - deviceTimestamp + 19800
      if (secondsAgo >= 60) {
        const minutesAgo = Math.floor(secondsAgo / 60)
        if (minutesAgo >= 60) {
          const hoursAgo = Math.floor(minutesAgo / 60)
          if (hoursAgo >= 24){
            const daysAgo = Math.floor(hoursAgo / 24)
            return daysAgo + " days ago"
          }
          else {
            return hoursAgo + " hours ago"
          }
        }
        else {
          return minutesAgo + " minutes ago"
        }
      }
      else {
        return secondsAgo + " seconds ago"
      }
    },
    isOnline(){
      const deviceTimestamp = this.$store.state.deviceStatus.status.timestamp
      const currentTimestamp = this.$store.state.deviceStatus.status.currentTime
      const secondsAgo = currentTimestamp - deviceTimestamp + 19800
      if (secondsAgo <= 15){
        return true
      }
      else{
        return false
      }
    }
  }
};
</script>
