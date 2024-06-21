package cz.cvut.fit.kuznear1.firebase.core.di

import com.google.firebase.analytics.FirebaseAnalytics
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.crashlytics.FirebaseCrashlytics
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.messaging.FirebaseMessaging
import org.koin.dsl.module

val coreModule = module {
    single { FirebaseAuth.getInstance() }
    single { FirebaseFirestore.getInstance() }
    single { FirebaseCrashlytics.getInstance() }
    single { FirebaseAnalytics.getInstance(get()) }
    single { FirebaseMessaging.getInstance() }
}
