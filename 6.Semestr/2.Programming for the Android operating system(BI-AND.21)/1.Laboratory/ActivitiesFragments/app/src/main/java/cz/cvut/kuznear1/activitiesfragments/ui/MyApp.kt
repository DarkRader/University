package cz.cvut.kuznear1.activitiesfragments.ui

import android.app.Application
import android.util.Log

class MyApp : Application() {

    override fun onCreate() {
        super.onCreate()
        Log.d("onCreate","app created")
    }
}
