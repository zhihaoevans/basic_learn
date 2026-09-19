import Foundation

// MARK: - 表达式解析器 (递归下降)

enum CalculatorError: Error, CustomStringConvertible {
    case divisionByZero
    case invalidExpression(String)
    case unexpectedEnd

    var description: String {
        switch self {
        case .divisionByZero:
            return "错误: 除以零"
        case .invalidExpression(let msg):
            return "错误: \(msg)"
        case .unexpectedEnd:
            return "错误: 表达式不完整"
        }
    }
}

/// 递归下降表达式求值器
struct ExpressionEvaluator {
    private var tokens: [Token]
    private var position: Int = 0

    init(expression: String) {
        self.tokens = ExpressionEvaluator.tokenize(expression)
    }

    /// 对外入口：解析并求值
    mutating func evaluate() throws -> Double {
        position = 0
        guard !tokens.isEmpty else { throw CalculatorError.invalidExpression("空表达式") }
        let result = try parseExpression()
        if position < tokens.count {
            throw CalculatorError.invalidExpression("多余的 token: '\(tokens[position..<tokens.count])'")
        }
        return result
    }

    // MARK: - 递归下降各层级

    /// expression = term (("+" | "-") term)*
    private mutating func parseExpression() throws -> Double {
        var left = try parseTerm()
        while position < tokens.count {
            let op = tokens[position]
            guard op == .plus || op == .minus else { break }
            position += 1
            let right = try parseTerm()
            left = (op == .plus) ? left + right : left - right
        }
        return left
    }

    /// term = factor (("*" | "/") factor)*
    private mutating func parseTerm() throws -> Double {
        var left = try parseFactor()
        while position < tokens.count {
            let op = tokens[position]
            guard op == .multiply || op == .divide else { break }
            position += 1
            let right = try parseFactor()
            if op == .divide {
                guard right != 0 else { throw CalculatorError.divisionByZero }
                left /= right
            } else {
                left *= right
            }
        }
        return left
    }

    /// factor = number | "(" expression ")" | ("+" | "-") factor
    private mutating func parseFactor() throws -> Double {
        guard position < tokens.count else {
            throw CalculatorError.unexpectedEnd
        }

        // 一元加减
        if tokens[position] == .plus || tokens[position] == .minus {
            let op = tokens[position]
            position += 1
            let value = try parseFactor()
            return (op == .minus) ? -value : value
        }

        // 括号
        if tokens[position] == .leftParen {
            position += 1
            let value = try parseExpression()
            guard position < tokens.count, tokens[position] == .rightParen else {
                throw CalculatorError.invalidExpression("缺少右括号")
            }
            position += 1
            return value
        }

        // 数字
        if case .number(let value) = tokens[position] {
            position += 1
            return value
        }

        throw CalculatorError.invalidExpression("意外的 token: '\(tokens[position])'")
    }

    // MARK: - 词法分析

    private enum Token: Equatable, CustomStringConvertible {
        case number(Double)
        case plus, minus, multiply, divide
        case leftParen, rightParen

        var description: String {
            switch self {
            case .number(let v):
                let s = String(format: "%g", v)
                return s
            case .plus: return "+"
            case .minus: return "-"
            case .multiply: return "*"
            case .divide: return "/"
            case .leftParen: return "("
            case .rightParen: return ")"
            }
        }
    }

    private static func tokenize(_ expr: String) -> [Token] {
        var tokens: [Token] = []
        var index = expr.startIndex

        while index < expr.endIndex {
            let ch = expr[index]

            if ch.isWhitespace {
                index = expr.index(after: index)
                continue
            }

            switch ch {
            case "+": tokens.append(.plus)
            case "-": tokens.append(.minus)
            case "*": tokens.append(.multiply)
            case "/": tokens.append(.divide)
            case "(": tokens.append(.leftParen)
            case ")": tokens.append(.rightParen)
            default:
                if ch.isNumber || ch == "." {
                    var numStr = ""
                    var hasDot = false
                    while index < expr.endIndex {
                        let c = expr[index]
                        if c == "." {
                            if hasDot { break }
                            hasDot = true
                            numStr.append(c)
                        } else if c.isNumber {
                            numStr.append(c)
                        } else {
                            break
                        }
                        index = expr.index(after: index)
                    }
                    guard let value = Double(numStr) else {
                        // 跳过无法解析的部分，让上层报错
                        continue
                    }
                    tokens.append(.number(value))
                    continue
                } else {
                    // 忽略未知字符，让解析阶段报错
                }
            }
            index = expr.index(after: index)
        }
        return tokens
    }
}
