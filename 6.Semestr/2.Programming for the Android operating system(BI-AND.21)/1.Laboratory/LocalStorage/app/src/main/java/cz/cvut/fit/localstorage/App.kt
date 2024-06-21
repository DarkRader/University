package cz.cvut.fit.localstorage

import android.app.Application
import android.content.Context

// This way of providing app's Context is used solely for the sake of simplicity. Use DI instead!
private lateinit var application: Application
val appContext: Context get() = application

class App : Application() {

    override fun onCreate() {
        super.onCreate()
        application = this
    }
}
