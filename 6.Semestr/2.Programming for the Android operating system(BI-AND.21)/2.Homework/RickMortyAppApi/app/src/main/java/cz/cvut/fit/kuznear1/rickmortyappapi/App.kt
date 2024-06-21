package cz.cvut.fit.kuznear1.rickmortyappapi

import android.app.Application
import cz.cvut.fit.kuznear1.rickmortyappapi.core.di.coreModule
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.di.characterModule
import org.koin.android.ext.koin.androidContext
import org.koin.core.context.startKoin

class App : Application() {

    override fun onCreate() {
        super.onCreate()
        startKoin {
            androidContext(this@App)
            modules(coreModule, characterModule)
        }
    }
}