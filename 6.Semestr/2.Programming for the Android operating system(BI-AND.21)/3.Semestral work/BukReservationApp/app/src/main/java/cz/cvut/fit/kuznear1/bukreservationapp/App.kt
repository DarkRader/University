package cz.cvut.fit.kuznear1.bukreservationapp

import android.app.Application
import cz.cvut.fit.kuznear1.bukreservationapp.core.di.coreModule
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.di.calendarModule
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.di.miniServiceModule
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.di.profileModule
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.di.reservationModule
import org.koin.android.ext.koin.androidContext
import com.google.firebase.crashlytics.FirebaseCrashlytics
import com.google.firebase.ktx.Firebase
import com.google.firebase.ktx.initialize
import org.koin.core.context.startKoin

@Suppress("DEPRECATION")
class App : Application() {

    override fun onCreate() {
        super.onCreate()

        Firebase.initialize(this)

        FirebaseCrashlytics.getInstance().setCrashlyticsCollectionEnabled(true)

        startKoin {
            androidContext(this@App)
            modules(coreModule, calendarModule, miniServiceModule, profileModule, reservationModule)
        }
    }
}