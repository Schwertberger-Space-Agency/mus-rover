import org.jetbrains.compose.desktop.application.dsl.TargetFormat

val ktorVersion: String by project
val sqlDelightVersion: String by project
val dateTimeVersion: String by project
val coroutinesVersion: String by project
val mqttVersion: String by project

plugins {
    kotlin("jvm")
    id("org.jetbrains.compose")
}

group = "hofwimmer.lukas"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
    maven("https://maven.pkg.jetbrains.space/public/p/compose/dev")
    google()
}

dependencies {
    // Note, if you develop a library, you should use compose.desktop.common.
    // compose.desktop.currentOs should be used in launcher-sourceSet
    // (in a separate module for demo project and in testMain).
    // With compose.desktop.common you will also lose @Preview functionality
    implementation(compose.desktop.currentOs)

    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:$coroutinesVersion")
    implementation("io.ktor:ktor-client-core:$ktorVersion")
    implementation("io.ktor:ktor-client-content-negotiation:$ktorVersion")
    implementation("io.ktor:ktor-serialization-kotlinx-json:$ktorVersion")
    implementation("com.squareup.sqldelight:runtime:$sqlDelightVersion")
    implementation("org.jetbrains.kotlinx:kotlinx-datetime:$dateTimeVersion")

    implementation("io.github.davidepianca98:kmqtt-common:$mqttVersion")
    implementation("io.github.davidepianca98:kmqtt-client:$mqttVersion")
}

compose.desktop {
    application {
        mainClass = "MainKt"

        nativeDistributions {
            targetFormats(TargetFormat.Exe, TargetFormat.Msi, TargetFormat.Deb)
            packageName = "compose-desktop-sandbox"
            packageVersion = "1.0.0"
        }
    }
}
