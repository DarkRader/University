package cz.cvut.fit.kuznear1.cameraapp.features.camera.presentation

import android.Manifest
import android.os.Build
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.res.stringResource
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import com.google.accompanist.permissions.rememberMultiplePermissionsState
import cz.cvut.fit.kuznear1.cameraapp.R

@OptIn(ExperimentalPermissionsApi::class)
@Composable
fun Permission(
    rationale: String,
    permissionNotAvailableContent: @Composable () -> Unit = {},
    content: @Composable () -> Unit = {},
) {
    val permissions: MutableList<String> = mutableListOf(Manifest.permission.CAMERA)
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
        permissions += Manifest.permission.POST_NOTIFICATIONS
    }
    val permissionState = rememberMultiplePermissionsState(permissions)

    if (permissionState.allPermissionsGranted) {
        content()
    } else {
        if (permissionState.shouldShowRationale) {
            AlertDialog(
                onDismissRequest = { },
                title = { Text(text = stringResource(id = R.string.permission_request)) },
                text = { Text(rationale) },
                confirmButton = {
                    Button(onClick = { permissionState.launchMultiplePermissionRequest() }) {
                        Text(text = stringResource(id = R.string.ok))
                    }
                }
            )
        } else {
            // Either user got a permission request for the first time or declined two times or more
            LaunchedEffect(Unit) {
                permissionState.launchMultiplePermissionRequest()
            }
            permissionNotAvailableContent()
        }
    }
}