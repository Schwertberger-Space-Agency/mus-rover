import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.CoroutineScope
import mqtt.MQTTVersion
import mqtt.packets.Qos
import mqtt.packets.mqttv5.ReasonCode

@OptIn(ExperimentalUnsignedTypes::class)
class MqttClient(
    private val topic: String
) {
    private var client: MQTTClient = MQTTClient(
        MQTTVersion.MQTT5,
        "broker.mqttdashboard.com",
        1883,
        null
    ) { message ->
        println(message.payload?.toByteArray()?.decodeToString())
    }

    fun connect() {
//        println("Connecting to MQTT broker")
    }

    fun disconnect() {
        println("Disconnecting from MQTT broker")
        client.disconnect(ReasonCode.SUCCESS)
    }

    fun publish(message: String, coroutineScope: CoroutineDispatcher) {
        println("Publishing message to topic $topic: $message")
        client.publish(false, Qos.EXACTLY_ONCE, topic, message.encodeToByteArray().toUByteArray())
        client.runSuspend(coroutineScope)
    }

    fun subscribe() {}

    fun unsubscribe() {}
}