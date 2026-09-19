import SwiftUI

/// 计算器 ViewModel —— 管理表达式构建与求值
final class CalculatorViewModel: ObservableObject {
    @Published var expression: String = ""
    @Published var result: String = ""

    /// 记录是否刚刚按下 "="，以便下次输入时自动清空
    private var justEvaluated = false

    // MARK: - 按钮处理

    func input(_ text: String) {
        // 如果上一步求了值，输入新内容时先清空
        if justEvaluated {
            expression = ""
            result = ""
            justEvaluated = false
        }
        expression.append(text)
    }

    func clear() {
        expression = ""
        result = ""
        justEvaluated = false
    }

    func backspace() {
        guard !expression.isEmpty else { return }
        expression.removeLast()
        result = ""
        justEvaluated = false
    }

    func evaluate() {
        guard !expression.isEmpty else { return }
        var evaluator = ExpressionEvaluator(expression: expression)
        do {
            let value = try evaluator.evaluate()
            if value == floor(value) && value.isFinite {
                result = String(Int64(value))
            } else {
                result = String(value)
            }
        } catch {
            result = "\(error)"
        }
        justEvaluated = true
    }
}
