package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.reservation

import android.annotation.SuppressLint
import android.webkit.WebView
import android.webkit.WebViewClient
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.viewinterop.AndroidView

@SuppressLint("SetJavaScriptEnabled")
@Composable
fun CalendarWebView(type: String) {
    var htmlContent by remember { mutableStateOf(generateHTML(type)) }

    LaunchedEffect(type) {
        htmlContent = generateHTML(type)
    }

    AndroidView(factory = { context ->
        WebView(context).apply {
            webViewClient = WebViewClient()
            settings.javaScriptEnabled = true
        }
    }, update = { webView ->
        webView.loadDataWithBaseURL(null, htmlContent, "text/html", "UTF-8", null)
    } )
}

private fun generateHTML(type: String): String {
    val calendarFrame = when (type) {
        "klub" -> {
            "<iframe src=\"https://calendar.google.com/calendar/embed?height=500&wkst=2&ctz=Europe%2FPrague&bgcolor=%23B39DDB&showTz=0&title=Club%20Room%20Reservation&hl=en_GB&showPrint=0&mode=MONTH&src=Y185MGMwNTM1ODNkNGQyYWUxNTY1NTFjNmVjZDMxMWY4N2RhZDYxMGEzMjcyNTQ1YzM2Mzg3OTY0NWY2OTY4Y2VmQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&src=Y19mOGE4N2JhZDlkZjYzODQxYTM0MzgzNWU2YzU1OTY0MzgzNWFhM2M5MDgzMDI2ODAzMjQ4MDdiNjFkY2I3ZTQ5QGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&src=Y18xOTU4NmEzZGE1MGNhMDY1NjZlZjYyMDEyZDY4MjllYmY0ZTMwMjYxMDgyMTJlOWY5ZDBjYzJmYzZiYzdjNDRhQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&src=Y180ZjNjY2I5YjI1ZTNlMzdiYzFkY2VhODc4NGE4YTExNDQyZDM5ZTcwMDgwOWExMmJlZTIxYmJlZWI2N2FmNzY1QGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&src=Y184ZmM4YzY3NjBmN2UzMmVkNTc3ODVjZjQ3MzlkYzYzZTQwNmI0YTgwMmFlZWM2NWNhMGIxYTNmNTY2OTYyNjNkQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&src=Y19hYzg5MzBiMDAwZTQzODE4NzA3ZDZmZjVlYzRlNDBiN2VmNTI5ZjRkYjc5MDg5Y2Q1YzNlZGFhM2I1OWZiNDFiQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&color=%23cc00a9&color=%230B8043&color=%238E24AA&color=%23616161&color=%23D50000&color=%23F6BF26\" style=\"border:solid 1px #777\" width=\"370\" height=\"500\" frameborder=\"0\" scrolling=\"no\"></iframe>"
        }
        "grill" -> {
            "<iframe src=\"https://calendar.google.com/calendar/embed?height=500&wkst=2&ctz=Europe%2FPrague&bgcolor=%23EF6C00&showTz=0&title=Grill%20Reservation&hl=en_GB&showPrint=0&mode=MONTH&src=Y182Y2FiMzM5NmYzZTBkNDAwZDA3OTA0YjA4ZjQyN2ZmOWM2NmI5MGI4MDk0ODhjZmU2NDAxYTg3ODkxYWIxY2ZkQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&color=%23EF6C00\" style=\"border:solid 1px #777\" width=\"370\" height=\"500\" frameborder=\"0\" scrolling=\"no\"></iframe>"
        }
        else -> {
            "<iframe src=\"https://calendar.google.com/calendar/embed?height=500&wkst=2&ctz=Europe%2FPrague&bgcolor=%233F51B5&showTz=0&title=Study%20Room%20Reservation&hl=en_GB&showPrint=0&mode=MONTH&src=Y184ZjA3YTA1NGRjNGNkMDJmODQ4NDkxZmZlZTlhZGIwMzAyNjExODExZTcxMWZmZTkyMWU0MDI1ZDE4ZDQyZWYyQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&src=Y182MDliYzRmZGVmZTMxMGUzMGRlYzAyZDkwNzUzZjQzNGQ4MmNkNzM4ODE4ZGVjNjc5YWQwMThkMTI3MzFmOTdmQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20&color=%233F51B5&color=%23039BE5\" style=\"border:solid 1px #777\" width=\"370\" height=\"500\" frameborder=\"0\" scrolling=\"no\"></iframe>"
        }
    }

    return """
        <!DOCTYPE html>
        <html>
        <head>
            <style>
                body, html {
                    height: 100%;
                    margin: 0;
                }
            </style>
        </head>
        <body>
            "$calendarFrame"
        </body>
        </html>
    """.trimIndent()
}
