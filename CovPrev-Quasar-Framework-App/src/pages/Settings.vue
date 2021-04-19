<template>
  <div class="q-pa-md">
    <div class="row q-col-gutter-y-md">
      <div class="col-12">
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="text-h6 q-mt-xs">
              Settings
            </div>
            <div class = "q-mt-sm"></div>
            <q-list>
              <q-item>
                <q-item-section>
                  <q-item-label>Online Refresh Time</q-item-label>
                  <q-item-label caption lines="4">If the app doesn't receive a Keep Alive Connection for {{ keepAliveTimer }} seconds, then the device will be declared offline. (Default: 15)
                  </q-item-label>
                </q-item-section>

                <q-item-section side top>
                  <q-item-label caption>App Setting</q-item-label>
                  <q-icon name="loop"/>
                </q-item-section>
              </q-item>

              <q-item>
                <q-item-section side>
                  <q-icon color="primary" name="hourglass_bottom" />
                </q-item-section>
                <q-item-section>
                  <q-slider
                    v-model="keepAliveTimer"
                    :min="10"
                    :max="60"
                    label
                    color="primary"
                  />
                  <!-- <div align="center">
                  <q-item-label caption>Admin Access Only.</q-item-label>
                  </div> -->
                </q-item-section>
                <q-item-section side>
                  <q-icon color="primary" name="hourglass_top" />
                </q-item-section>
              </q-item>
              <q-separator spaced inset />
              <q-item>
                <q-item-section>
                  <q-item-label>Temperature Range</q-item-label>
                  <q-item-label caption>The acceptable temperature range of the MLX90614 IR Temperature sensor is between {{ tempRange.min }}°F and {{ tempRange.max }}°F. (Default: 96.5°F and 98.9°F)</q-item-label>
                </q-item-section>

                <q-item-section side top>
                  <q-item-label caption>Device Setting</q-item-label>
                  <q-icon name="compare_arrows"/>
                </q-item-section>
              </q-item>
              <q-item>
                <q-item-section side>
                  <q-icon color="primary" name="vertical_align_bottom" />
                </q-item-section>
                <q-item-section>
                  <q-range
                  disable
                    v-model="tempRange"
                    :min="95"
                    :max="105"
                    :step="0.1"
                    label
                  />
                  <div align="center">
                  <q-item-label caption>Admin Access Only.</q-item-label>
                  </div>
                </q-item-section>
                <q-item-section side>
                  <q-icon color="primary" name="vertical_align_top" />
                </q-item-section>
              </q-item>
              <q-separator spaced inset />
              <q-item>
                <q-item-section>
                  <q-item-label>Oxygen Percentage Range</q-item-label>
                  <q-item-label caption>The acceptable SpO₂% range of the MAX30100 Pulse Oximeter sensor is between {{ spo2Range.min }}% and {{ spo2Range.max }}%. (Default: 93% and 100%)</q-item-label>
                </q-item-section>

                <q-item-section side top>
                  <q-item-label caption>Device Setting</q-item-label>
                  <q-icon name="compare_arrows"/>
                </q-item-section>
              </q-item>
              <q-item>
                <q-item-section side>
                  <q-icon color="primary" name="vertical_align_bottom" />
                </q-item-section>
                <q-item-section>
                  <q-range
                  disable
                    v-model="spo2Range"
                    :min="85"
                    :max="100"
                    label
                  />   
                  <div align="center">
                  <q-item-label caption>Admin Access Only.</q-item-label>
                  </div>
                </q-item-section>
                <q-item-section side>
                  <q-icon color="primary" name="vertical_align_top" />
                </q-item-section>
              </q-item>
              <q-separator spaced inset />
              <q-item>
                <q-item-section>
                  <q-item-label>Pulse Range</q-item-label>
                  <q-item-label caption>The acceptable pulse range of the MAX30100 Pulse Oximeter sensor is between {{ pulseRange.min }}BPM and {{ pulseRange.max }}BPM. (Default: 60BPM and 110BPM%)</q-item-label>
                </q-item-section>

                <q-item-section side top>
                  <q-item-label caption>Device Setting</q-item-label>
                  <q-icon name="compare_arrows"/>
                </q-item-section>
              </q-item>
              <q-item>
                <q-item-section side>
                  <q-icon color="primary" name="vertical_align_bottom" />
                </q-item-section>
                <q-item-section>
                  <q-range
                  disable
                    v-model="pulseRange"
                    :min="50"
                    :max="150"
                    label
                  />   
                  <div align="center">
                  <q-item-label caption>Admin Access Only.</q-item-label>
                  </div>
                </q-item-section>
                <q-item-section side>
                  <q-icon color="primary" name="vertical_align_top" />
                </q-item-section>
              </q-item>
            </q-list>
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
      keepAliveTimer: 15,
      tempRange: {
        min: 96.5,
        max: 98.9
      },
      spo2Range: {
        min: 93,
        max: 100
      },
      pulseRange: {
        min: 60,
        max: 110
      }
    };
  },
  methods() {}
};
</script>
