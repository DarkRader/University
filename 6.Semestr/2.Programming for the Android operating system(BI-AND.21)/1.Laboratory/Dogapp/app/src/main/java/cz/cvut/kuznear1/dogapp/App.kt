package cz.cvut.kuznear1.dogapp

import android.app.Application
import cz.cvut.kuznear1.dogapp.core.di.coreModule
import cz.cvut.kuznear1.dogapp.features.breed.di.breedModule
import cz.cvut.kuznear1.dogapp.features.fact.di.factModule
import org.koin.android.ext.koin.androidContext
import org.koin.core.context.startKoin

class App : Application() {

    override fun onCreate() {
        super.onCreate()
        startKoin {
            androidContext(this@App)
            modules(coreModule, breedModule, factModule)
        }
    }
}