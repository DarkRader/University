package cz.cvut.fit.kuznear1.firebase

import android.app.NotificationManager
import android.content.Context
import android.graphics.Color
import androidx.core.app.NotificationCompat
import com.google.firebase.messaging.FirebaseMessagingService
import com.google.firebase.messaging.RemoteMessage
import kotlin.random.Random

class MessagingService : FirebaseMessagingService() {

    override fun onMessageReceived(message: RemoteMessage) {
        super.onMessageReceived(message)
        val title = message.notification?.title
        val body = message.notification?.body

        val notification = NotificationCompat.Builder(this, getString(R.string.general_channel_id))
            .setContentTitle(title)
            .setContentText(body)
            .setSmallIcon(R.drawable.ic_notes)
            .setColor(Color.BLUE)
            .build()

        val notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        notificationManager.notify(Random.nextInt(), notification)
    }
}
