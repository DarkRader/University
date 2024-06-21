package cz.cvut.fit.kuznear1.cameraapp.features.camera.presentation

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.provider.Settings
import android.util.Log
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageCapture
import androidx.camera.core.ImageCapture.CAPTURE_MODE_MAXIMIZE_QUALITY
import androidx.camera.core.ImageCaptureException
import androidx.camera.core.UseCase
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalLifecycleOwner
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import androidx.core.net.toUri
import coil.compose.rememberAsyncImagePainter
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import cz.cvut.fit.kuznear1.cameraapp.R
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import org.koin.androidx.compose.koinViewModel
import java.io.File
import java.util.concurrent.Executor
import kotlin.coroutines.resume
import kotlin.coroutines.resumeWithException
import kotlin.coroutines.suspendCoroutine


@OptIn(ExperimentalPermissionsApi::class)
@Composable
fun CameraScreen(
    modifier: Modifier = Modifier,
    viewModel: CameraViewModel = koinViewModel(),
) {
    val emptyImageUri = Uri.parse("file://dev/null")
    var imageUri by remember { mutableStateOf(emptyImageUri) }
    val context = LocalContext.current
    val lifecycleOwner = LocalLifecycleOwner.current

    var previewUseCase by remember { mutableStateOf<UseCase>(androidx.camera.core.Preview.Builder().build()) }
    val imageCaptureUseCase by remember {
        mutableStateOf(
            ImageCapture.Builder()
                .setCaptureMode(CAPTURE_MODE_MAXIMIZE_QUALITY)
                .build()
        )
    }
    val coroutineScope = rememberCoroutineScope()
    if (imageUri != emptyImageUri) {
        Box(modifier = modifier) {
            Image(
                modifier = Modifier.fillMaxSize(),
                painter = rememberAsyncImagePainter(
                    imageUri
                ),
                contentDescription = null
            )
            Button(
                modifier = Modifier.align(Alignment.BottomCenter),
                onClick = {
                    imageUri = emptyImageUri
                    viewModel.sendNotification()
                }
            ) {
                Text(stringResource(id = R.string.upload_image))
            }
        }
    } else {
        Permission(rationale = stringResource(id = R.string.rationale),
            permissionNotAvailableContent = {
                Column(modifier) {
                    Text(stringResource(id = R.string.no_camera))
                    Button(
                        onClick = {
                            context.startActivity(
                                Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS).apply {
                                    data = Uri.fromParts("package", context.packageName, null)
                                }
                            )
                        }
                    ) {
                        Text(stringResource(id = R.string.go_to_settings))
                    }
                }
            }) {
            Box(contentAlignment = Alignment.BottomCenter) {
                CameraPreview(
                    modifier = Modifier.fillMaxSize(),
                    onUseCase = {
                        previewUseCase = it
                    }
                )
                CapturePictureButton(
                    modifier = Modifier
                        .padding(16.dp),
                    onClick = {
                        coroutineScope.launch {
                            imageCaptureUseCase.takePicture(context.executor).let { file ->
                                imageUri = file.toUri()
                            }
                        }
                    }
                )
                LaunchedEffect(previewUseCase) {
                    val cameraProvider = context.getCameraProvider()
                    try {
                        cameraProvider.unbindAll()
                        cameraProvider.bindToLifecycle(
                            lifecycleOwner,
                            CameraSelector.DEFAULT_BACK_CAMERA,
                            previewUseCase,
                            imageCaptureUseCase
                        )
                    } catch (ex: Exception) {
                        Log.e("CameraCapture", "Failed to bind camera use cases", ex)
                    }
                }
            }
        }
    }
}


suspend fun ImageCapture.takePicture(executor: Executor): File {
    val imageFile = withContext(Dispatchers.IO) {
        kotlin.runCatching {
            File.createTempFile("image", "png")
        }.getOrElse { ex ->
            Log.e("TakePicture", "Failed to create temporary file", ex)
            File("/dev/null")
        }
    }

    return suspendCoroutine { continuation ->
        val outputOptions = ImageCapture.OutputFileOptions.Builder(imageFile).build()
        takePicture(
            outputOptions,
            executor,
            object : ImageCapture.OnImageSavedCallback {
                override fun onImageSaved(output: ImageCapture.OutputFileResults) {
                    continuation.resume(imageFile)
                }

                override fun onError(ex: ImageCaptureException) {
                    Log.e("TakePicture", "Image capture failed", ex)
                    continuation.resumeWithException(ex)
                }
            }
        )
    }
}

val Context.executor: Executor
    get() = ContextCompat.getMainExecutor(this)

suspend fun Context.getCameraProvider(): ProcessCameraProvider =
    suspendCoroutine { continuation ->
        ProcessCameraProvider.getInstance(this).also { future ->
            future.addListener(
                {
                    continuation.resume(future.get())
                },
                executor
            )
        }
    }


@Preview
@Composable
fun CapturePictureButton(modifier: Modifier = Modifier, onClick: () -> Unit = {}) {
    Button(
        modifier = modifier.size(120.dp),
        shape = CircleShape,
        colors = ButtonDefaults.buttonColors(
            containerColor = Color.Black
        ),
        onClick = onClick
    ) {}
}