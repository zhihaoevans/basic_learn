import SwiftUI

struct ContentView: View {
    @EnvironmentObject var vm: CalculatorViewModel

    var body: some View {
        VStack(spacing: 0) {
            DisplayView()
            ButtonGridView()
        }
        .frame(width: 320, height: 480)
    }
}

// MARK: - 显示屏

struct DisplayView: View {
    @EnvironmentObject var vm: CalculatorViewModel

    var body: some View {
        VStack(alignment: .trailing, spacing: 8) {
            // 表达式区域
            ScrollView(.horizontal) {
                Text(vm.expression.isEmpty ? " " : vm.expression)
                    .font(.system(size: 28, weight: .light))
                    .foregroundColor(.gray)
                    .lineLimit(1)
            }
            .frame(maxWidth: .infinity, alignment: .trailing)
            .frame(height: 36)

            // 结果区域
            Text(vm.result.isEmpty ? " " : vm.result)
                .font(.system(size: 40, weight: .medium))
                .foregroundColor(.white)
                .lineLimit(1)
                .frame(height: 44)
        }
        .padding(.horizontal, 20)
        .padding(.top, 20)
        .padding(.bottom, 12)
        .frame(maxWidth: .infinity)
        .frame(height: 120)
        .background(Color(white: 0.15))
    }
}

// MARK: - 按钮区域

struct ButtonGridView: View {
    var body: some View {
        VStack(spacing: 1) {
            // 第一行：括号、清除
            HStack(spacing: 1) {
                CalcButton("(", type: .function)
                CalcButton(")", type: .function)
                CalcButton("C", type: .clear)
                CalcButton("÷", type: .operation)
            }
            // 第二行
            HStack(spacing: 1) {
                CalcButton("7", type: .digit)
                CalcButton("8", type: .digit)
                CalcButton("9", type: .digit)
                CalcButton("×", type: .operation)
            }
            // 第三行
            HStack(spacing: 1) {
                CalcButton("4", type: .digit)
                CalcButton("5", type: .digit)
                CalcButton("6", type: .digit)
                CalcButton("−", type: .operation)
            }
            // 第四行
            HStack(spacing: 1) {
                CalcButton("1", type: .digit)
                CalcButton("2", type: .digit)
                CalcButton("3", type: .digit)
                CalcButton("+", type: .operation)
            }
            // 第五行
            HStack(spacing: 1) {
                CalcButton("0", type: .digit, width: 159.5)
                CalcButton(".", type: .digit)
                CalcButton("=", type: .equals)
            }
        }
        .frame(maxHeight: .infinity)
    }
}

// MARK: - 单个按钮

struct CalcButton: View {
    @EnvironmentObject var vm: CalculatorViewModel

    let label: String
    let type: ButtonType
    var width: CGFloat = 80

    init(_ label: String, type: ButtonType, width: CGFloat = 80) {
        self.label = label
        self.type = type
        self.width = width
    }

    enum ButtonType {
        case digit, operation, function, clear, equals
    }

    var body: some View {
        Button(action: handlePress) {
            Text(label)
                .font(.system(size: 26, weight: type == .digit ? .regular : .medium))
                .frame(width: width, height: 72)
                .background(bgColor)
                .foregroundColor(fgColor)
        }
        .buttonStyle(.plain)
    }

    private func handlePress() {
        switch label {
        case "C":
            vm.clear()
        case "=":
            vm.evaluate()
        case "÷":
            vm.input("/")
        case "×":
            vm.input("*")
        case "−":
            vm.input("-")
        default:
            vm.input(label)
        }
    }

    // MARK: 颜色

    private var bgColor: Color {
        switch type {
        case .digit:    return Color(white: 0.24)
        case .operation: return Color.orange
        case .function: return Color(white: 0.42)
        case .clear:    return Color(white: 0.42)
        case .equals:   return Color.orange
        }
    }

    private var fgColor: Color {
        switch type {
        case .digit:    return .white
        case .operation: return .white
        case .function: return .white
        case .clear:    return .white
        case .equals:   return .white
        }
    }
}

// MARK: - 预览

#Preview {
    ContentView()
        .environmentObject(CalculatorViewModel())
}
