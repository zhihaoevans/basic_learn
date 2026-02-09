<template>
  <div class="dashboard-container">
    <el-container>
      <el-header>
        <div class="header-content">
          <h2>AI SaaS Dashboard</h2>
          <el-button type="danger" @click="handleLogout">Logout</el-button>
        </div>
      </el-header>
      
      <el-main>
        <el-row :gutter="20">
          <el-col :span="8">
            <el-card class="dashboard-card">
              <template #header>
                <div class="card-header">
                  <span>API Usage</span>
                </div>
              </template>
              <div class="card-content">
                <el-statistic title="Total Requests" :value="1234" />
              </div>
            </el-card>
          </el-col>
          
          <el-col :span="8">
            <el-card class="dashboard-card">
              <template #header>
                <div class="card-header">
                  <span>Credits</span>
                </div>
              </template>
              <div class="card-content">
                <el-statistic title="Available Credits" :value="500" />
              </div>
            </el-card>
          </el-col>
          
          <el-col :span="8">
            <el-card class="dashboard-card">
              <template #header>
                <div class="card-header">
                  <span>Active Models</span>
                </div>
              </template>
              <div class="card-content">
                <el-statistic title="Models in Use" :value="3" />
              </div>
            </el-card>
          </el-col>
        </el-row>

        <el-row :gutter="20" class="mt-4">
          <el-col :span="24">
            <el-card>
              <template #header>
                <div class="card-header">
                  <span>Recent Activity</span>
                </div>
              </template>
              <el-table :data="recentActivity" style="width: 100%">
                <el-table-column prop="date" label="Date" width="180" />
                <el-table-column prop="type" label="Type" width="180" />
                <el-table-column prop="description" label="Description" />
                <el-table-column prop="status" label="Status">
                  <template #default="scope">
                    <el-tag :type="scope.row.status === 'success' ? 'success' : 'danger'">
                      {{ scope.row.status }}
                    </el-tag>
                  </template>
                </el-table-column>
              </el-table>
            </el-card>
          </el-col>
        </el-row>
      </el-main>
    </el-container>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import { useUserStore } from '../stores/user'

const userStore = useUserStore()

const recentActivity = ref([
  {
    date: '2024-03-20 10:00',
    type: 'API Call',
    description: 'Text Generation Request',
    status: 'success'
  },
  {
    date: '2024-03-20 09:45',
    type: 'API Call',
    description: 'Image Analysis',
    status: 'success'
  },
  {
    date: '2024-03-20 09:30',
    type: 'System',
    description: 'Credit Update',
    status: 'success'
  }
])

const handleLogout = () => {
  userStore.logout()
}
</script>

<style scoped>
.dashboard-container {
  min-height: 100vh;
  background-color: #f0f2f5;
}

.el-header {
  background-color: white;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  padding: 0 20px;
}

.header-content {
  height: 60px;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.el-main {
  padding: 20px;
}

.dashboard-card {
  height: 100%;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.card-content {
  text-align: center;
  padding: 20px 0;
}

.mt-4 {
  margin-top: 20px;
}
</style> 