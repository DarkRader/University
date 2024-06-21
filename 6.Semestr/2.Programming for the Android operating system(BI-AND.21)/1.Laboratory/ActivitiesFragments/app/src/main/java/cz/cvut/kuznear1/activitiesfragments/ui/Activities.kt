package cz.cvut.kuznear1.activitiesfragments.ui

import android.content.Context
import android.content.Intent
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.util.Log
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import cz.cvut.kuznear1.activitiesfragments.R

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MainActivityScreen(
                onAddActivityClick = {
                    startActivity(Intent(this, SensorActivity::class.java))
                },
            )
        }
    }
}

class SensorActivity : AppCompatActivity() {

    private val eventListener = EventListener()
    private lateinit var sensorManager: SensorManager
    private lateinit var sensor: Sensor

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
        sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)!!
    }

    override fun onStart() {
        super.onStart()
        sensorManager.registerListener(eventListener, sensor, SensorManager.SENSOR_DELAY_NORMAL)
    }

    override fun onStop() {
        super.onStop()
        sensorManager.unregisterListener(eventListener)
    }

    private class EventListener : SensorEventListener {

        override fun onSensorChanged(event: SensorEvent?) {
            if (event != null) {
                Log.d("sensor event", "${event.values.firstOrNull()}")
            }
        }

        override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) = Unit
    }
}

class MainFragmentActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_fragment_activity)
    }
}