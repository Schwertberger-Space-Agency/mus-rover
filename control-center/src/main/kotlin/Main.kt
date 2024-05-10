import androidx.compose.desktop.ui.tooling.preview.Preview
import androidx.compose.foundation.layout.Column
import androidx.compose.material.Button
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.material.TextField
import androidx.compose.runtime.*
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application
import kotlinx.coroutines.CoroutineDispatcher

enum class Direction(val value: String) {
    W("W"),
    S("S"),
    L("L"),
    R("R")
}

enum class Velocity(val value: String) {
    B("B"),
    E("E")
}

@Composable
@Preview
fun App() {
    MaterialTheme {
        var location by remember { mutableStateOf("Europe/Paris") }
        var timeAtLocation by remember { mutableStateOf("No location selected") }

        Column {
            Text(timeAtLocation)
            TextField(value = location, onValueChange = { location = it })
            Button(onClick = { timeAtLocation = "13:30" }) {
                Text("Show Time At Location")
            }
        }
    }
}

@Composable
fun sendMessage(direction: Direction, velocity: Velocity) {
    val coroutineScope = rememberCoroutineScope()
    val client by remember { mutableStateOf(MqttClient("mus-rover/in-controls")) }
    client.publish(direction.value + velocity.value, )
}

fun main() = application {
    Window(onCloseRequest = ::exitApplication) {
        App()
    }
}
