// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "Zendesk Sunshine Conversations",
    platforms: [
        .iOS(.v12)
    ],
    products: [
        .library(
            name: "Smooch",
            targets: ["Smooch"])
    ],
    targets: [
        .binaryTarget(
            name: "Smooch",
            path: "Smooch.xcframework"
        )
    ]
)
