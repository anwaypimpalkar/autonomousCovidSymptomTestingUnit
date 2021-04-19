<template>
  <div class="q-pa-md">
    <div class="row q-col-gutter-y-md">
      <div class="col-12">
        
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Abstract</div>
          </q-card-section>
          <q-separator inset />
          <q-card-section>
            • In the unprecedented pandemic times where it is of prime necessity for everyone to maintain social distancing, keeping in mind the new normal we have designed a contactless COVID-19 testing unit.
            <div class = "q-mt-xs"></div>• This completely automated 3-subsystem unit enables large institutions like hospitals, theatres, malls to keep a check on the population and the stored data enables them to take see the trends in their institutions and take the necessary prevention measures.
            <div class = "q-mt-xs"></div>• The cost-effectiveness of a system like this can be critical in projects like these, so the plan has been made keeping that in mind.
          </q-card-section>
        </q-card>
        <div class = "q-mt-md"></div>
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Overview</div>
          </q-card-section>
          <q-separator inset />
          <q-card-section>
            The project consists of three subsystems:
            <div class = "q-mt-xs"></div>
            <q-list dense>
              <q-item>1. Sanitization Spray</q-item>
              <q-item>2. Thermometer and Pulse Oximeter</q-item>
              <q-item>3. Data Management and App</q-item>
            </q-list>
            The data collected from the device is uploaded to a cloud based database and will be processed and fed to machine learning algorithms and made accessible through an app. We will study trends which will help dynamically vary the optimal acceptable temperature, pulse and SpO₂% measurements.          </q-card-section>
        </q-card>
        <div class = "q-mt-md"></div>
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Block Diagram</div>
          </q-card-section>
          <q-separator inset />
          <q-card-section>
            <q-img
              src = "~assets/block_diagram.jpg"
              class=""
            />  
            <div align="center">
              <q-item-label caption>Overall Block Diagram</q-item-label>
            </div>
            <div class = "q-mt-sm">
              <q-separator inset/>
            </div>
            <q-img
              src = "~assets/nodemcu.png"
              class=""
            />  
            <div align="center">
              <q-item-label caption>Data Management Subsystem Block Diagram</q-item-label>
            </div>
          </q-card-section>
          
        </q-card>
        <div class = "q-mt-md"></div>
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Components</div>
          </q-card-section>
          <q-separator inset />
          <q-card-section>
            <q-img
              src = "~assets/components.png"
              class=""
            />  
            <div align="center">
              <q-item-label caption>List of Hardware and Software Used</q-item-label>
            </div>
          </q-card-section>
        </q-card>
<div class = "q-mt-md"></div>
        <q-btn outline type="a" href="https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit" target="_blank" color="primary" class="full-width" icon="code" label="Project Files and APK" />  
        
<div class = "q-ma-sm"></div>
      <q-btn outline type="a" href="https://drive.google.com/file/d/1NYCh3wmoTx2HUUAF4v0lXH8njgkQsBvl/view?usp=sharing" color="primary" class="full-width" icon="movie" label="Video Demonstration" /> 
        <div class = "q-ma-sm"></div>
        <q-btn outline type="a" href="https://drive.google.com/uc?export=download&id=1ZmO6GE364_erbTjJOaccKt0A7-JQBltU" target="_blank" color="primary" class="full-width" icon="show_chart" label="Presentation PDF" />
        
        <div class = "q-mt-md"></div>
        <q-card flat bordered class="my-card">
          <q-card-section>
            <div class="text-h6">Group 18 Details</div>
          </q-card-section>
          <q-separator inset />
          <q-card-section>
            <b>Members:</b>
            <div class = "q-mt-xs"></div>
            <q-list dense>
              <q-item>1. Esha Dorle (111907070)</q-item>
              <q-item>2. Ishita Rathor (111807046)</q-item>
              <q-item>3. Anway Pimpalkar (111907066)</q-item>
              <q-item>4. Kushagra Shrivastava (111907074)</q-item>
              <q-item>5. Shubham Mujumdar (111907081)</q-item>
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
      message: "device page"
    };
  },
  methods: {
    methods: {
  }
  }
};
</script>