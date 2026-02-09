import { defineStore } from 'pinia'
import { ref } from 'vue'
import axios from 'axios'
import router from '../router'

export const useUserStore = defineStore('user', () => {
  const token = ref(localStorage.getItem('token') || '')
  const userInfo = ref(null)

  const login = async (credentials) => {
    try {
      // 这里替换为实际的API接口
      const response = await axios.post('/api/login', credentials)
      const { token: newToken, user } = response.data
      
      token.value = newToken
      userInfo.value = user
      localStorage.setItem('token', newToken)
      
      router.push('/dashboard')
      return true
    } catch (error) {
      console.error('Login failed:', error)
      return false
    }
  }

  const logout = () => {
    token.value = ''
    userInfo.value = null
    localStorage.removeItem('token')
    router.push('/login')
  }

  return {
    token,
    userInfo,
    login,
    logout
  }
}) 