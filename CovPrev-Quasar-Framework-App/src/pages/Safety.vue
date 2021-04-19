<template>
  <div class="q-pa-md">
    <div class="row q-col-gutter-y-md">
      <div class="col-12">
        <q-card bordered class="my-card">
          <q-card-section>
            <div class="row">
              <div class="col-8 text-h6">
                <div class="text-h6 q-mt-xs">
                  Device Status
                </div>
              </div>
              <div class="col-4">
                <q-chip square class="col-4 float-right">
                  <q-avatar
                    icon="signal_wifi_4_bar"
                    color="green"
                    text-color="white"
                    class="on-right"
                  />
                  Online
                </q-chip>
              </div>
            </div>

            <q-separator />
          </q-card-section>
          <q-card-section class="q-pt-none">
            Last seen: 16:20:20 20/4/2021
            <br />
            Latest ID Number: CovPrev-0000420
          </q-card-section>
          <q-separator inset />

          <q-card-actions vertical>
            <q-btn bordered flat>Refresh</q-btn>
          </q-card-actions>
        </q-card>
      </div>
      <div class="col-12">
        <q-card bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Sensor Status</div>
            <q-separator />
          </q-card-section>

          <q-card-section class="q-pt-none">
            <q-card flat bordered class="my-card">
              <q-card-section>
                <div class="row">
                  <div class="col-8 text-h6">
                    <div class="text-h6 q-mt-xs">
                      Temperature
                    </div>
                  </div>
                  <div class="col-4">
                    <q-chip square class="col-4 float-right">
                      <q-avatar
                        icon="close"
                        color="red"
                        text-color="white"
                        class="on-right"
                      />
                      Down
                    </q-chip>
                  </div>
                </div>
              </q-card-section>
            </q-card>
            <div class = "q-mt-xs"></div>
            <q-card flat bordered class="my-card">
              <q-card-section>
                <div class="row">
                  <div class="col-8 text-h6">
                    <div class="text-h6 q-mt-xs">
                      Temperature
                    </div>
                  </div>
                  <div class="col-4">
                    <q-chip square class="col-4 float-right">
                      <q-avatar
                        icon="close"
                        color="red"
                        text-color="white"
                        class="on-right"
                      />
                      Down
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
      message: "device page"
    };
  },
  methods() {}
};
</script>
