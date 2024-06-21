package cz.cvut.fit.kuznear1.firebase

import android.app.Application
import android.app.NotificationChannel
import android.app.NotificationManager
import android.os.Build
import com.google.firebase.messaging.FirebaseMessaging
import cz.cvut.fit.kuznear1.firebase.core.di.coreModule
import cz.cvut.fit.kuznear1.firebase.features.notes.di.notesModule
import cz.cvut.fit.kuznear1.firebase.features.profile.di.profileModule
import org.koin.android.ext.android.inject
import org.koin.android.ext.koin.androidContext
import org.koin.core.context.startKoin

class App : Application() {

    private val firebaseMessaging by inject<FirebaseMessaging>()

    override fun onCreate() {
        super.onCreate()
        startKoin {
            androidContext(this@App)
            modules(coreModule, notesModule, profileModule)
        }

        // Notification channels have to be used from Android 8.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val notificationManager = getSystemService(NotificationManager::class.java)
            notificationManager.createNotificationChannel(
                NotificationChannel(
                    getString(R.string.general_channel_id),
                    getString(R.string.general_channel_name),
                    NotificationManager.IMPORTANCE_DEFAULT
                )
            )
        }

        firebaseMessaging.subscribeToTopic("news")
    }
}
