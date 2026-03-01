const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const scoreElement = document.getElementById('score');
const highScoreElement = document.getElementById('high-score');
const startBtn = document.getElementById('start-btn');
const overlay = document.getElementById('game-overlay');
const overlayTitle = document.getElementById('overlay-title');

// Game constants
const GRID_SIZE = 20;
const TILE_COUNT = canvas.width / GRID_SIZE;
const GAME_SPEED = 100; // ms per frame

// Game state
let score = 0;
let highScore = localStorage.getItem('snakeHighScore') || 0;
let snake = [];
let food = { x: 15, y: 15 };
let dx = 0;
let dy = 0;
let gameInterval;
let isGameRunning = false;

// Initialize high score display
highScoreElement.innerText = highScore;

// Colors
const SNAKE_COLOR = '#00ffcc';
const FOOD_COLOR = '#ff00ff';

function initGame() {
    snake = [
        { x: 10, y: 10 },
        { x: 9, y: 10 },
        { x: 8, y: 10 }
    ];
    score = 0;
    dx = 1; // Start moving right
    dy = 0;
    scoreElement.innerText = score;
    spawnFood();
    isGameRunning = true;
    overlay.classList.add('hidden');

    if (gameInterval) clearInterval(gameInterval);
    gameInterval = setInterval(gameLoop, GAME_SPEED);
}

function gameLoop() {
    if (!isGameRunning) return;
    update();
    draw();
}

function update() {
    // Move snake head
    const head = { x: snake[0].x + dx, y: snake[0].y + dy };

    // Wall collision
    if (head.x < 0 || head.x >= TILE_COUNT || head.y < 0 || head.y >= TILE_COUNT) {
        gameOver();
        return;
    }

    // Self collision
    for (let i = 0; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            gameOver();
            return;
        }
    }

    snake.unshift(head);

    // Eat food
    if (head.x === food.x && head.y === food.y) {
        score += 10;
        scoreElement.innerText = score;
        if (score > highScore) {
            highScore = score;
            highScoreElement.innerText = highScore;
            localStorage.setItem('snakeHighScore', highScore);
        }
        spawnFood();
    } else {
        snake.pop();
    }
}

function draw() {
    // Clear canvas
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Draw Food
    ctx.fillStyle = FOOD_COLOR;
    ctx.shadowBlur = 15;
    ctx.shadowColor = FOOD_COLOR;
    ctx.beginPath();
    ctx.arc(
        food.x * GRID_SIZE + GRID_SIZE / 2,
        food.y * GRID_SIZE + GRID_SIZE / 2,
        GRID_SIZE / 2 - 2,
        0,
        Math.PI * 2
    );
    ctx.fill();

    // Draw Snake
    ctx.fillStyle = SNAKE_COLOR;
    ctx.shadowBlur = 10;
    ctx.shadowColor = SNAKE_COLOR;
    snake.forEach((segment, index) => {
        // Head is slightly larger or different distinct feature could be added here
        ctx.fillRect(
            segment.x * GRID_SIZE + 1,
            segment.y * GRID_SIZE + 1,
            GRID_SIZE - 2,
            GRID_SIZE - 2
        );
    });

    // Reset shadow for performance or other elements
    ctx.shadowBlur = 0;
}

function spawnFood() {
    food = {
        x: Math.floor(Math.random() * TILE_COUNT),
        y: Math.floor(Math.random() * TILE_COUNT)
    };
    // Make sure food doesn't spawn on snake
    for (let segment of snake) {
        if (food.x === segment.x && food.y === segment.y) {
            spawnFood();
            return;
        }
    }
}

function gameOver() {
    isGameRunning = false;
    clearInterval(gameInterval);
    overlayTitle.innerText = "GAME OVER";
    startBtn.innerText = "PLAY AGAIN";
    overlay.classList.remove('hidden');
}

// Input handling
let changingDirection = false;

function gameLoop() {
    if (!isGameRunning) return;
    changingDirection = false;
    update();
    draw();
}

document.addEventListener('keydown', (e) => {
    // Prevent default scrolling for arrow keys
    if (["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"].indexOf(e.code) > -1) {
        e.preventDefault();
    }

    if (changingDirection || !isGameRunning) return;

    const goingUp = dy === -1;
    const goingDown = dy === 1;
    const goingRight = dx === 1;
    const goingLeft = dx === -1;

    switch (e.key) {
        case 'ArrowUp':
        case 'w':
        case 'W':
            if (!goingDown) { dx = 0; dy = -1; changingDirection = true; }
            break;
        case 'ArrowDown':
        case 's':
        case 'S':
            if (!goingUp) { dx = 0; dy = 1; changingDirection = true; }
            break;
        case 'ArrowLeft':
        case 'a':
        case 'A':
            if (!goingRight) { dx = -1; dy = 0; changingDirection = true; }
            break;
        case 'ArrowRight':
        case 'd':
        case 'D':
            if (!goingLeft) { dx = 1; dy = 0; changingDirection = true; }
            break;
    }
});

startBtn.addEventListener('click', initGame);
