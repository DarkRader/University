package cz.cvut.fit.kuznear1.cameraapp.features.camera.presentation

import android.content.Context
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.work.Constraints
import androidx.work.NetworkType
import androidx.work.OneTimeWorkRequestBuilder
import androidx.work.WorkManager
import cz.cvut.fit.kuznear1.cameraapp.features.notification.data.NotificationHelper
import cz.cvut.fit.kuznear1.cameraapp.features.notification.data.NotificationWorker
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class CameraViewModel(
    private val notificationHelper: NotificationHelper,
) : ViewModel(),
    KoinComponent {
    private val context: Context by inject()

    private val notificationConstraints =
        Constraints.Builder().setRequiredNetworkType(NetworkType.CONNECTED).build()

    fun sendNotification() {
        viewModelScope.launch {
            val showNotificationRequest =
                OneTimeWorkRequestBuilder<NotificationWorker>().setConstraints(
                    notificationConstraints
                ).build()

            WorkManager.getInstance(context).enqueue(showNotificationRequest)

            // was used in the lecture
//            notificationHelper.showProgressNotification()
        }
    }
}