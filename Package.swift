// swift-tools-version: 5.8
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
	name: "scas",
	products: [
		.library(name: "ScasKit", targets: ["ScasKit"]),
	],
	targets: [
		.target(name: "ScasKit"),

		.executableTarget(
			name: "tables",
			resources: [
				.copy("z80.tab")
			]),

		.executableTarget(
			name: "scas",
			dependencies: ["ScasKit"]),

		.executableTarget(
			name: "scdump",
			dependencies: ["ScasKit"]),

		.executableTarget(
			name: "scwrap",
			dependencies: ["ScasKit"]),
	],
	cLanguageStandard: .c2x
)
