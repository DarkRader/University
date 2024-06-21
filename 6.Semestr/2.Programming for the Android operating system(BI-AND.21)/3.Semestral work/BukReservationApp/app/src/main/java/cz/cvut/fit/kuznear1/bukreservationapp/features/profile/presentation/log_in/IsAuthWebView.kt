package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.log_in

import android.annotation.SuppressLint
import android.net.Uri
import android.webkit.WebResourceRequest
import android.webkit.WebView
import android.webkit.WebViewClient
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.viewinterop.AndroidView

@SuppressLint("SetJavaScriptEnabled")
@Composable
fun AuthIsWebView(onCodeReceived: (String) -> Unit) {
    val authIsUrl = "https://is.buk.cvut.cz/oauth/authorize?client_id=e36219f8fdd7619dfa80754aa17c47e38c04e4407d37c26e48058531c82b18c1&response_type=code&scope=location&redirect_uri=https://rezervace.buk.cvut.cz:8000/auth_is/login/callback"

    var currentUrl by remember { mutableStateOf(authIsUrl) }

    AndroidView(factory = { context ->
        WebView(context).apply {
            webViewClient = object : WebViewClient() {
                override fun shouldOverrideUrlLoading(view: WebView, request: WebResourceRequest): Boolean {
                    currentUrl = request.url.toString()
                    return super.shouldOverrideUrlLoading(view, request)
                }

                override fun onPageFinished(view: WebView, url: String) {
                    super.onPageFinished(view, url)
                    currentUrl = url

                    if (url.startsWith("https://rezervace.buk.cvut.cz:8000/auth_is/login/callback")) {
                        val uri = Uri.parse(url)
                        val code = uri.getQueryParameter("code")
                        if (code != null) {
                            onCodeReceived(code)
                        }
                    }
                }
            }
            settings.javaScriptEnabled = true
            loadUrl(authIsUrl)
        }
    })
}
