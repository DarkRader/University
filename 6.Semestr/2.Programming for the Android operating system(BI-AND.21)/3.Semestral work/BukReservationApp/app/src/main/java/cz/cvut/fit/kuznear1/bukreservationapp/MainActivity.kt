package cz.cvut.fit.kuznear1.bukreservationapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import com.google.firebase.analytics.FirebaseAnalytics
import com.google.firebase.crashlytics.FirebaseCrashlytics
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.MainScreen
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.theme.BukReservationAppTheme

class MainActivity : ComponentActivity() {
    private lateinit var firebaseAnalytics: FirebaseAnalytics

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        firebaseAnalytics = FirebaseAnalytics.getInstance(this)
        val bundle = Bundle().apply {
            putString(FirebaseAnalytics.Param.METHOD, "MainActivity")
        }
        firebaseAnalytics.logEvent(FirebaseAnalytics.Event.APP_OPEN, bundle)

        FirebaseCrashlytics.getInstance().log("MainActivity created")

        setContent {
            BukReservationAppTheme {
                MainScreen()
            }
        }
    }
}
