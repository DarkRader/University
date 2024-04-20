package cz.cvut.fit.kuznear1.cameraapp

import android.app.Application
import cz.cvut.fit.kuznear1.cameraapp.core.di.workerModule
import cz.cvut.fit.kuznear1.cameraapp.features.camera.di.cameraModule
import cz.cvut.fit.kuznear1.cameraapp.features.notification.di.notificationModule
import org.koin.android.ext.koin.androidContext
import org.koin.androidx.workmanager.koin.workManagerFactory
import org.koin.core.context.startKoin

class App : Application() {

    override fun onCreate() {
        super.onCreate()
        startKoin {
            androidContext(this@App)
            workManagerFactory()
            modules(cameraModule, notificationModule, workerModule)
        }
    }
}